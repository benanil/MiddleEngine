#pragma once

#include "Entity.hpp"
#include "Component.hpp"

namespace MiddleEngine
{
	class Transform : public Component
	{
		glm::vec3 eulerAngles;
		EventFloatPtr OnTransformChanged;
		bool disposed;
	public:
		~Transform();
		Transform(const Entity* _entity);
		Transform* parent;
		
		glm::mat4* matrix;
		glm::vec3 position   ;
		glm::vec3 scale      ;
		glm::vec3 eulerDegree;
		glm::quat rotation   ;

		const glm::mat4& GetMatrix()      const { return *matrix    ; }
		const glm::vec3& GetPosition()    const { return position   ; }
		const glm::vec3& GetScale()       const { return scale      ; }
		const glm::vec3& GetEulerAngles() const { return eulerAngles; }
		const glm::quat& GetRotation()    const { return rotation   ; }

		void SetMatrix     (const glm::mat4& mat4 , bool updateMatrix = true);
		void SetPosition   (const glm::vec3& vec3 , bool updateMatrix = true);
		void SetScale      (const glm::vec3& vec3 , bool updateMatrix = true);
		void SetEulerAngles(const glm::vec3& euler, bool updateMatrix = true);
		void SetRotation   (const glm::quat& quat , bool updateMatrix = true);

		void Update(const float& dt);
		void Start();
		void OnValidate();
		void OnImgui();
		void Save();
		void Load();

		void AddOnTransformChanged(CallbackFloatPtr action);
		void UpdateTranslation(bool notify = true);
	};
}

