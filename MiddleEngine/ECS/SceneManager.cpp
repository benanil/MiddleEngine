#include "Scene.hpp"
#include "Entity.hpp"
#include <spdlog/spdlog.h>

namespace MiddleEngine
{
	namespace SceneManager
	{
		Scene* scenes[12];
		unsigned char sceneCount;
		Scene* CurrentScene;

		void Update()
		{
			if (CurrentScene) {
				CurrentScene->Update();
			}
		}

		void UpdateEditor() 
		{
			if (CurrentScene) {
				CurrentScene->EditorUpdate();
			}
		}

		Scene* GetActiveScene() { return CurrentScene; }
		const unsigned char SceneManager::SceneCount() { return sceneCount; }
		
		void DeleteScene(const char* name) {
			unsigned char index = 0;
			for (; index < sceneCount; index++) {
				if (scenes[index]->name == name) break;
			}
			DeleteScene(index);
		}
		
		void DeleteScene(const unsigned char& index) {
			if (sceneCount == 0) return; // we need at least 1 scene
			// delete scene
			scenes[index]->~Scene();
			delete scenes[index];
			sceneCount--; // decrement scene count
		
			scenes[index] = scenes[sceneCount]; // move last ptr to removed index
			scenes[index]->index = index;
		
			scenes[sceneCount] = nullptr;
		}
		
		void AddScene(Scene* scene) {
			scene->index = sceneCount;
			scenes[sceneCount++] = scene;
		}
		
		void LoadScene(const unsigned char& index) {
			if (CurrentScene) CurrentScene->Destroy();
			CurrentScene = scenes[index];
			scenes[index]->Load();
		}
		
		void LoadScene(std::string_view name) {
			for (unsigned char i = 0; i < sceneCount; i++)
			{
				if (scenes[i]->name == name)
				{
					CurrentScene = scenes[i];
					scenes[i]->Load();
					break;
				}
			}
		}
	}
	
}