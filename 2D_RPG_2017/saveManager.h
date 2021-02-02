#pragma once
#include "singletonBase.h"

struct tagPlayerData
{
	int hp;
	float x, y;
};

class saveManager : public singletonBase<saveManager>
{
private:
	tagPlayerData playerData;

public:
	HRESULT init();
	void release();

	int getPlayerHp() { return playerData.hp; }
	float getPlayerX() { return playerData.x; }
	float getPlayerY() { return playerData.y; }

	void loadPlayerData();
	void savePlayerData(int hp, float x, float y);

};

