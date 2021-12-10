#include "Component.hpp"
#include "Entity.hpp"
#include "Scene.hpp"
#include "Transform.hpp"

namespace MiddleEngine
{
	Entity::~Entity() {
		if (disposed) return;
		for (unsigned char i = 0; i < companentCount; i++)
		{
			companents[i]->OnRemoved();
			delete companents[i];
		}
		transform->~Transform();
		delete(transform);
		this->OnRemoved();
	}

	Entity::Entity() : name("entity"), transform(new Transform(this)) {

	}

	Entity::Entity(const char* Name)
		: name(Name) , transform(new Transform(this)){
		SceneManager::GetActiveScene()->AddEntity(this);
	}

	void Entity::Update(const float& dt) {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->Update(dt);
		}
	}

	void Entity::Start() {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->Start();
		}
	}

	void Entity::OnValidate() {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->OnValidate();
		}
	}

	void Entity::OnImgui()
	{
		transform->OnImgui();
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->OnImgui();
		}
	}
	
	void Entity::Save() {
		
	}

	void Entity::Load() {

	}

	const Component* Entity::GetCompanent(unsigned char& index) const
	{
		return companents[index];
	}

	template<typename Component> const Component* Entity::GetCompanent() const
	{
		for (unsigned char i = 0; i < companentCount; i++)
		{
			if (typeid(Component).hash_code() == typeid(companents[i]).hash_code())
			{
				return GetCompanent(i);
			}
		}
		return nullptr;
	}
	
	void Entity::AddCompanent(Component* companent) {
		companents[companentCount++] = companent;
	}

	void Entity::RemoveCompanent(int index)
	{
		if(companentCount == 0) return;
		companents[index]->OnRemoved();
		delete companents[index];
		
		companentCount--;
		companents[index] = companents[companentCount];
	}

	template<typename T> void Entity::RemoveCompanent() {
		for (unsigned char i = 0; i < companentCount; i++)
		{
			if (typeid(T).hash_code() == typeid(companents[i]).hash_code())
			{
				RemoveCompanent(i);
				break;
			}
		}
	}
}

