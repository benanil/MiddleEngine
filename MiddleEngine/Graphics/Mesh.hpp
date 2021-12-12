#pragma once
#include "VulkanMemory.hpp"
#include <spdlog/spdlog.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 
#include "../Common.hpp"

namespace MiddleEngine
{
	struct Vertex 
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoord;

		Vertex () = default;
		Vertex (Vertex&&) = default;

		static std::vector<VkVertexInputBindingDescription> getBindingDescription() {
			std::vector<VkVertexInputBindingDescription> BindingDescriptions(1);

			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			BindingDescriptions[0] = bindingDescription;
			return BindingDescriptions;
		}

		static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, normal);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}
	};

	class SubMesh
	{
	public:
		Vertex* vertices;
		uint32_t* indices;
		MDBuffer indexBuffer;
		MDBuffer vertexBuffer;
		uint32_t vertexCount;
		uint32_t indexCount;
		
		const char* path;
		const char* name;
		
		SubMesh(const aiMesh* aimesh, const std::string& _path)
			: path(_path.c_str()), name(aimesh->mName.C_Str())
		{
			vertexCount = aimesh->mNumVertices;
			indexCount = aimesh->mNumFaces * 3;
			
			vertices = static_cast<Vertex*>(malloc(vertexCount * sizeof(Vertex)));
			indices = static_cast<uint32_t*>(malloc(indexCount * sizeof(uint32_t)));

			// copy indices from aimesh's faces
			for (size_t i = 0; i < aimesh->mNumFaces; i++) {

				indices[i * 3 + 0] = aimesh->mFaces[i].mIndices[0];
				indices[i * 3 + 1] = aimesh->mFaces[i].mIndices[1];
				indices[i * 3 + 2] = aimesh->mFaces[i].mIndices[2];
			}

			VulkanMemory::CreateBuffer(
				indices, 
				indexCount * sizeof(uint32_t), 
				VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
				VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, MD_MAP_BIT, indexBuffer);

			for (size_t  i = 0; i < vertexCount; i++) 
			{
				vertices[i].pos.x = aimesh->mVertices[i].x;
				vertices[i].pos.y = aimesh->mVertices[i].y;
				vertices[i].pos.z = aimesh->mVertices[i].z;
				
				vertices[i].normal.x = aimesh->mNormals[i].x;
				vertices[i].normal.y = aimesh->mNormals[i].y;
				vertices[i].normal.z = aimesh->mNormals[i].z;

				vertices[i].texCoord.x = aimesh->mTextureCoords[0][i].x;
				vertices[i].texCoord.y = aimesh->mTextureCoords[0][i].y;
			}

			VulkanMemory::CreateBuffer(
				vertices,
				vertexCount * sizeof(Vertex),
				VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
				VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, MD_MAP_BIT, vertexBuffer);
		}

		void Dispose(const VkDevice& device)
		{
			indexBuffer.Dispose(device);
			vertexBuffer.Dispose(device);
			delete vertices;
			delete indices;
		}
	};

	struct MDMesh
	{
		SubMesh* submeshes;
		uint16_t submeshSize;
		
		MDMesh() = default;
		MDMesh(SubMesh* _submeshes, uint16_t _submeshSize) : submeshes(_submeshes), submeshSize(_submeshSize) {}

		SubMesh& operator [](uint16_t index)
		{
			return submeshes[index];
		}

		void Dispose(const VkDevice& device) const 
		{
			for (size_t i = 0; i < submeshSize; i++)
			{
				submeshes[i].Dispose(device);
			}
		}
	};

	namespace MeshLoader
	{
		static MDMesh LoadMesh(const std::string& path)
		{
			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs);

			// If the import failed, report it
			if (scene == nullptr) {
				printf(importer.GetErrorString());
				assert(1);
			}

			SubMesh* submeshes = (SubMesh*)malloc(sizeof(SubMesh) * scene->mNumMeshes);

			uint16_t i = 0;
			
			for (; i < scene->mNumMeshes; i++)
			{
				submeshes[i] = SubMesh(scene->mMeshes[i], path);
			}

			MDMesh result(submeshes, i);

			importer.FreeScene();

			return result;
		}
	}

}

