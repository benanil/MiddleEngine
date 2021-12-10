#pragma once
#include "../MiddleEngine.hpp"
#include <list>
#include <string>
#include "Entity.hpp"
#include <filesystem>

namespace MiddleEngine
{
	class Scene
	{
		Entity* entities[2048];
		unsigned short entityCount;
		bool disposed;
		void InspectorWindow() const;
		void HierarchyWindow() const;
	public:
		std::string path;
		const char* name;
		unsigned char index;
	public:
		~Scene();
		Scene();
		Scene(const char* path);
		static Entity* CurrentEntity;
		static void SetCurrentEntity(Entity* entity);
		static Scene* Create(const char* name);
		void Start() const;
		void Update() const;
		void Save() const;
		void EditorUpdate() const;
		void Load();
		void Destroy();
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);
	};

	namespace SceneManager 
	{
		void Update();								 
		void UpdateEditor();
		Scene* GetActiveScene();
		void DeleteScene(const unsigned char& index);
		void DeleteScene(const char* name)			;
		void AddScene(Scene* scene)					;
		void LoadScene(const unsigned char& index)	;
		void LoadScene(std::string_view name)		;
		const unsigned char SceneCount()			;
	}

	// save scenes as binary
	class SceneSaver
	{
	public:
		static void Save(std::string_view path);
		static Scene Load(std::string_view path);
	};
}

