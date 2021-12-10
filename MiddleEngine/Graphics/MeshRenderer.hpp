#pragma once
#include "../ECS/ECS.hpp"
#include "VulkanMemory.hpp"
#include "Mesh.hpp"

namespace MiddleEngine
{
	
	class MeshRenderer : public Component
	{
	public:
		// MDMesh* mesh;
		// uint16_t index; // at vulkan backend's matrices
	
		~MeshRenderer()
		{
			// mesh->Dispose();
		}
	
		void TransformationChanged(const void* matrix) const
		{
			// VulkanBackend::FlushMeshRenderer(index, matrix);
		}
	
		MeshRenderer(const Entity* entity
			//, MDMesh* _mesh
		) : Component(entity, "Mesh Renderer") // , mesh(_mesh)
		{
			// index = VulkanBackend::AddMeshRenderer(
			// 	entity->GetCompanent<Transform>()->GetMatrix(), this);
		}
	
		void Update(const float& dt) override {}
		void Start()                 override {}
		void OnValidate()            override {}
		void OnImgui()               override {}
	};

}

