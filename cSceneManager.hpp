#pragma once
typedef struct SceneKey
{
	SHORT sceneIndex;
	string sceneName;

	SceneKey() : sceneIndex(0), sceneName("EmptyScene") {}
	SceneKey(SHORT index) : sceneIndex(index), sceneName() {}
	SceneKey(string name) : sceneIndex(-1), sceneName(std::move(name)) {}
	SceneKey(SHORT index, string name) : sceneIndex(index), sceneName(name) {}

	bool operator< (SceneKey rhs) const
	{
		return sceneIndex < rhs.sceneIndex;
	}
}SceneKey;
class cSceneManager : public cSingleton<cSceneManager>, public IFlowBase
{
public:
	typedef pair<SceneKey, shared_ptr<cScene>> ScenePair;
public:
	// IFlowBase을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	
	template<typename T> 
	ScenePair CreateScenePair(const SceneKey key)
	{
		if (std::is_class<T>::value) {
			return cSceneManager::ScenePair(key, dynamic_pointer_cast<cScene>(make_shared<T>()));
		}
	}

	shared_ptr<cScene> AddScene(const ScenePair pair);
	shared_ptr<cScene> LoadScene(const SceneKey key);
private:
	shared_ptr<cScene> m_CurScene;
	shared_ptr<cScene> m_NewScene;


	map<SceneKey, shared_ptr<cScene>> m_Scenes;
	

};
#define SCENE cSceneManager::GetInstance()
