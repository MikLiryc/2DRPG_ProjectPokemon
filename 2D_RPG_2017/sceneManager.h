#pragma once
#include "singletonBase.h"
//#include "gameNode.h" �̱������� ������� Ŭ�������� ���ӳ�忡 ���� �Ұ�

//=============================================================
//	## sceneManager ## �� �Ŵ��� 
//=============================================================

//�̱��� ��ӹ��� Ŭ�������� static���� ��������� ������, �Ϲ� Ŭ������ ���ӳ�带 ����ϸ� ����
//���ӳ�� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<std::string, gameNode*> mSceneList;
	typedef map<std::string, gameNode*>::iterator mSceneListIter;

	mSceneList _mSceneList;		//������ ���� ��Ƶ� ��
	mSceneListIter _mSceneIter;		//�� ���ͷ�����

	gameNode* _currentScene;	//���� ��
	gameNode* _prevScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�� �߰�
	gameNode* addScene(std::string sceneName, gameNode* scene);
	//�� ����
	HRESULT loadScene(std::string sceneName);

	gameNode* findScene(std::string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

