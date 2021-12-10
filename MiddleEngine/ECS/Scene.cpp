#include "Scene.hpp"
#include "Entity.hpp"
#include "spdlog/spdlog.h"
// #include "imgui/imgui.hpp"
// #include "../Rendering/Renderer.h"
// #include "../Editor/Editor.h"
#include "../Main/Time.hpp"

namespace MiddleEngine
{

	Scene::~Scene() {
		if (disposed == true) return;
		disposed = true;
		spdlog::warn("scene removed from the memory");
		Destroy();
	}

	Scene::Scene() : path("Scenes/default.scene"), name("default") 
	{
		spdlog::info("scene added to scenes");
		SceneManager::AddScene(this);
	}

	Scene* Scene::Create(const char* name) {
		auto scene = new Scene();
		scene->name = name;
		scene->index = SceneManager::SceneCount();
		SceneManager::AddScene(scene);
		return scene;
	}


	Scene::Scene(const char* path) {
		// to be continued
	}

	void Scene::Start() const {
		for (unsigned char i = 0; i < entityCount; i++) {
			entities[i]->Start();
		}
	}

	void Scene::Update() const {
		for (unsigned char i = 0; i < entityCount; i++) {
			entities[i]->Update(Time::deltaTime);
		}
	}

	// use json serialization after that we may change to binary
	void Scene::Save() const {  }

	// use json serialization after that we may change to binary
	void Scene::Load() {  }

	void Scene::Destroy() {

		for (unsigned char i = 0; i < entityCount; i++) {
			delete(entities[i]);
			entities[i] = nullptr;
		}
		
		entityCount = 0;
	}

	void Scene::EditorUpdate() const {
		InspectorWindow();
		HierarchyWindow();
	}

	Entity* Scene::CurrentEntity = NULL;

	void Scene::SetCurrentEntity(Entity* entity)
	{
		CurrentEntity = entity;
	}
	
	void Scene::InspectorWindow() const {
		// ImGui::Begin("Properties");
		// ImGui::Separator();
		// if (ImGui::BeginTabBar("Theme"))
		// {
		// 	if (ImGui::TabItemButton("Half Life")) Editor::HalfLifeTheme();
		// 	if (ImGui::TabItemButton("Dark")) Editor::DarkTheme();
		// }
		// ImGui::EndTabBar();
		// if (CurrentEntity) { CurrentEntity->OnImgui(); }
		// ImGui::End();
	}

	void Scene::HierarchyWindow() const
	{
		// ImGui::Begin("Inspector");
		// 
		// for (unsigned char i = 0; i < entityCount; i++) 
		// {
		// 	if (ImGui::TreeNode(entities[i]->name)) 
		// 	{
		// 		ImGui::TreePop();
		// 	}
		// }
		// ImGui::End();
	}

	void Scene::AddEntity(Entity* entity) 
	{
		entities[entityCount++] = entity;
	}

	void Scene::RemoveEntity(Entity* entity) 
	{
		unsigned short oldIndex = entity->globalIndex;
		entities[oldIndex]->~Entity();
		delete entities[oldIndex];
		entities[oldIndex] = nullptr; // for dangling pointer
		
		entityCount--;
		// moves last entity ptr to removed entity's position
		entities[oldIndex] = entities[entityCount];
		entities[entityCount] = nullptr; 
	}


	// SAVE LOAD
	void SceneSaver::Save(std::string_view path) {
	
	}
	
	Scene SceneSaver::Load(std::string_view path) {
		return Scene();
	}
}