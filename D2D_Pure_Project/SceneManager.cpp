#include "stdafx.h"
#include "SceneManager.h"

cApplication* SceneManager::CurrentScene = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	_mIter iter = mScene.begin();
	for (iter; iter != mScene.end(); ++iter) {
		SafeDeleteClass(iter->second);
	}
	mScene.clear();
}

void SceneManager::Update(void)
{
	if (CurrentScene)
		CurrentScene->Update();
}

void SceneManager::Render(void)
{
	if (CurrentScene)
		CurrentScene->Render();
}

cApplication * SceneManager::CreateScene(string SceneName, cApplication * Scene)
{
	if (!Scene) return nullptr;
	mScene.insert(make_pair(SceneName, Scene));
	return Scene;
}

HRESULT SceneManager::ChangeScene(string SceneName)
{
	_mIter iter = mScene.find(SceneName);
	if (iter == mScene.end()) return E_FAIL;
	if (iter->second == CurrentScene) return S_OK;

	if (SUCCEEDED(iter->second->Init())) {
		if (CurrentScene) CurrentScene->Release();
		CurrentScene = iter->second;
		return S_OK;
	}
	return E_FAIL;
}
