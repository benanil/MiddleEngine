#pragma once
#include "../MiddleEngine.hpp"
#include "Transform.hpp"
#include "Component.hpp"

namespace MiddleEngine
{
	class Transform;

	class Entity 
	{
		Component* companents[12];
		unsigned char companentCount;
		bool disposed;
	public:
		Transform* transform;
		/// <summary> if anything referancing this companent
		/// must aware of ve are deleting it, we don't want to deal with dangling pointers</summary>
		Event OnRemoved;
		std::string name;
		/// <summary> entitys id in the scene's entity stack </summary>
		unsigned short globalIndex;
	public:
		~Entity();
		Entity();
		Entity(const char* _name);

		void Update(const float& dt);
		void Start();
		void OnValidate();
		void OnImgui();
		void Save();
		void Load();

		template<typename Component> 
		const Component* GetCompanent() const;
		const Component* GetCompanent(unsigned char& index) const ;
		
		void AddCompanent(Component* companent);
		
		void RemoveCompanent(int index);
		template<typename Component> void RemoveCompanent();
	};
}

