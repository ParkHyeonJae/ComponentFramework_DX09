#include "DXUT.h"
#include "cSceneManager.hpp"

void cSceneManager::Init()
{
}

void cSceneManager::Release()
{

	for (auto& scenePair : m_Scenes)
	{
		scenePair.second->Release();
	}

}

void cSceneManager::Update()
{

	if (m_NewScene)
	{
		if (m_CurScene)
		{
			m_CurScene->Release();
			m_CurScene = nullptr;
		}
		m_CurScene = m_NewScene;
		m_CurScene->Init();
		m_NewScene = nullptr;
	}

	if (m_CurScene)
	{
		m_CurScene->Update();
	}

}

void cSceneManager::Render()
{

	if (m_CurScene)
		m_CurScene->Render();

}

shared_ptr<cScene> cSceneManager::AddScene(const ScenePair pair)
{
	m_Scenes.insert(pair);
	return m_Scenes[pair.first];
}

shared_ptr<cScene> cSceneManager::LoadScene(const SceneKey key)
{
	if (key.sceneIndex != -1) {
		m_NewScene = Utils::cUtils::HasMapKey<SceneKey, shared_ptr<cScene>, SHORT>(m_Scenes, key.sceneIndex);
		assert(m_NewScene != nullptr);
		return m_NewScene;
	}
	if (!key.sceneName.empty()) {
		m_NewScene = Utils::cUtils::HasMapKey<SceneKey, shared_ptr<cScene>, string>(m_Scenes, key.sceneName);
		assert(m_NewScene != nullptr);
		return m_NewScene;
	}
	return nullptr;
}
