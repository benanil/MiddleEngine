#include "Transform.hpp"
#include "../Graphics/MeshRenderer.hpp"
// #include "imgui/imgui.h"

namespace MiddleEngine
{
	void DecomposeMtx(const glm::mat4& m, glm::vec3& pos, glm::quat& rot, glm::vec3& scale);

	Transform::~Transform()  {
		if (disposed) return;
		disposed = true;
		OnRemoved();
	}

	Transform::Transform(const Entity* _entity) : Component(_entity, "Transform"),
		rotation(glm::identity<glm::quat>()),
		matrix  (new glm::mat4(1)),
		scale   (glm::vec3(1.0f)) {
	}

	void Transform::Update(const float& dt) { }
	void Transform::Start() { }
	
	void Transform::Save() {}
	void Transform::Load() {}

	void Transform::OnValidate() {
		UpdateTranslation();
	}
	
	void Transform::OnImgui() {

		// if (ImGui::CollapsingHeader("Transform")) {
		// 	if (ImGui::DragFloat3("Position", &position.x, 0.1f)) UpdateTranslation();
		// 	if (ImGui::DragFloat3("Euler", &eulerDegree.x, 0.1f)) SetEulerAngles(eulerDegree);
		// 	if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0, 1000)) UpdateTranslation();
		// }
	}

	void Transform::AddOnTransformChanged(CallbackFloatPtr action) 
	{ 
		OnTransformChanged.Add(action); 
	}


	void Transform::UpdateTranslation(bool notify) 
	{
		
		*matrix = glm::identity<glm::mat4>() * glm::toMat4(rotation) *
				  glm::scale(scale) * glm::translate(position);

		// const MeshRenderer* renderer = entity->GetCompanent<MeshRenderer>();
		// 
		// if (renderer)
		// {
		// 	renderer->TransformationChanged(matrix);
		// }

		if (notify) {
			OnTransformChanged.Invoke(reinterpret_cast<const float*>(matrix));
		}
	}

	void Transform::SetMatrix(const glm::mat4& mat4s, bool updateMatrix) {
		*matrix = mat4s;
		
		DecomposeMtx(mat4s, position, rotation, scale);

		eulerAngles = glm::eulerAngles(rotation);
		eulerDegree = glm::degrees(eulerAngles);
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetPosition(const glm::vec3& vec, bool updateMatrix) {
		position = vec;
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetScale(const glm::vec3& vec, bool updateMatrix) {
		scale = vec;
		if (updateMatrix) UpdateTranslation();
	}

	/// <param name="euler">in degree</param>
	void Transform::SetEulerAngles(const glm::vec3& euler, bool updateMatrix) {
		eulerDegree = euler;
		eulerAngles = glm::radians(eulerDegree);
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetRotation(const glm::quat& quat, bool updateMatrix) {
		rotation = quat;
		eulerAngles = glm::eulerAngles(rotation);
		eulerDegree = glm::degrees(eulerAngles);
		if (updateMatrix) UpdateTranslation();
	}

	void DecomposeMtx(const glm::mat4& m, glm::vec3& pos, glm::quat& rot, glm::vec3& scale)
	{
		pos = m[3];
		for (int i = 0; i < 3; i++)
			scale[i] = glm::length(glm::vec3(m[i]));
		const glm::mat3 rotMtx(
			glm::vec3(m[0]) / scale[0],
			glm::vec3(m[1]) / scale[1],
			glm::vec3(m[2]) / scale[2]);
		rot = glm::quat_cast(rotMtx);
	}
}