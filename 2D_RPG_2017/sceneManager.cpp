#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
}

void sceneManager::update()
{
	//현재 씬이 존재한다면 해당 씬을 업데이트
	if (_currentScene) _currentScene->update();

}

void sceneManager::render()
{
	//현재 씬이 존재한다면 해당 씬을 렌더
	if (_currentScene) _currentScene->render();
}

gameNode* sceneManager::addScene(std::string sceneName, gameNode* scene)
{
	//씬이 없으면 널 리턴
	if (!scene) { return NULL; }

	//씬이 있다면 그 씬을 반환하고 맵에 담아두기
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::loadScene(std::string sceneName)
{
	mSceneListIter find = _mSceneList.find(sceneName);

	//못찾았다면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재 씬이 같다면 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//큰 문제가 없다면 씬을 변경처리
	if (SUCCEEDED(find->second->init()))
	{
		_prevScene = _currentScene;
		_currentScene = find->second;
		return S_OK;
	}
}

gameNode* sceneManager::findScene(std::string sceneName)
{
	mSceneListIter key = _mSceneList.find(sceneName);

	if (key != _mSceneList.end())
	{
		return key->second;
	}

	return nullptr;
}
