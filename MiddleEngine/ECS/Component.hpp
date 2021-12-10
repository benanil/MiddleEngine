#pragma once
#include "../MiddleEngine.hpp"

namespace MiddleEngine
{
	class Entity;

	class Component abstract 
	{
		bool disposed;
	public:
		/// <summary> correspanding entity</summary>
		const Entity* entity;
		/// <summary> if anything referancing this companent
		/// must avare of ve are deleting it, we don't want to deal with dangling pointers</summary>
		Event OnRemoved;
		std::string name;
	public:
		Component(const Entity* _entity, const char* _name)
			: name(_name), entity(_entity) { }
		virtual void Update(const float& dt) = 0;
		virtual void Start() = 0;
		virtual void OnValidate() = 0;
		virtual void OnImgui() = 0;
	};
	
}