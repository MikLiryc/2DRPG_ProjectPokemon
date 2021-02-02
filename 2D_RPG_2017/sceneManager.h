#pragma once
#include "singletonBase.h"
//#include "gameNode.h" 싱글톤으로 만들어진 클래스에서 게임노드에 접근 불가

//=============================================================
//	## sceneManager ## 씬 매니저 
//=============================================================

//싱글톤 상속받은 클래스들은 static으로 만들어지기 때문에, 일반 클래스인 게임노드를 사용하면 터짐
//게임노드 전방선언
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<std::string, gameNode*> mSceneList;
	typedef map<std::string, gameNode*>::iterator mSceneListIter;

	mSceneList _mSceneList;		//각각의 씬을 담아둘 맵
	mSceneListIter _mSceneIter;		//맵 이터레이터

	gameNode* _currentScene;	//현재 씬
	gameNode* _prevScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가
	gameNode* addScene(std::string sceneName, gameNode* scene);
	//씬 변경
	HRESULT loadScene(std::string sceneName);

	gameNode* findScene(std::string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

