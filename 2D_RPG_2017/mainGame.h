#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "characterCreationScene.h"
#include "inGameScene.h"
#include "battleScene.h"

class mainGame : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

};