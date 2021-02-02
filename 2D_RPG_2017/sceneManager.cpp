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
	//���� ���� �����Ѵٸ� �ش� ���� ������Ʈ
	if (_currentScene) _currentScene->update();

}

void sceneManager::render()
{
	//���� ���� �����Ѵٸ� �ش� ���� ����
	if (_currentScene) _currentScene->render();
}

gameNode* sceneManager::addScene(std::string sceneName, gameNode* scene)
{
	//���� ������ �� ����
	if (!scene) { return NULL; }

	//���� �ִٸ� �� ���� ��ȯ�ϰ� �ʿ� ��Ƶα�
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::loadScene(std::string sceneName)
{
	mSceneListIter find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���� ���ٸ� E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//ū ������ ���ٸ� ���� ����ó��
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
