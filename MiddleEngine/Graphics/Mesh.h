#pragma once
#include "VulkanMemory.hpp"
#include <spdlog/spdlog.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 

namespace Rendering
{
	struct Mesh
	{
		Vertex* vertices;
		uint32_t* indices;
		unsigned int vertexCount;
		unsigned int indexCount;
		
		const char* path;
		const char* name;
		
		Mesh(const aiMesh* aimesh, const std::string& _path)
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
		}
	};

	struct MeshHandle
	{
		uint16_t size;
		Mesh* meshes;

		const Mesh& operator[](uint16_t i)
		{
			return meshes[i];
		}

		void Dispose()
		{
			for (uint16_t i = 0; i < size; i++)
			{
				delete meshes[i].indices;
				delete meshes[i].vertices;
			}
		}
	};

	static MeshHandle LoadMesh(const std::string& path, unsigned short& meshCount)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs);

		// If the import failed, report it
		if (scene == nullptr) {
			printf(importer.GetErrorString());
			assert(1);
		}

		meshCount = scene->mNumMeshes;
		Mesh* result = (Mesh*)malloc(sizeof(Mesh) * scene->mNumMeshes);

		unsigned short i = 0;
		for (; i < scene->mNumMeshes; i++)
		{
			result[i] = Mesh(scene->mMeshes[i], path);
		}

		importer.FreeScene();

		return { i, result };
	}

}

