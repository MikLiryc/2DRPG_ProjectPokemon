#pragma once
#include "gameNode.h"

class inGameScene : public gameNode
{
private:
	image* optionBox;
	image* goldRoomLimit;
	image* goldRoomBackground;
	image* goldHouseLimit;
	image* goldHouse;
	image* villageLimit;
	image* village;
	image* villagePond;
	image* pokeLab;
	image* pokeLabLimit;
	image* goldOverWorld;
	image* DrGongOverWorld;
	image* pokeBall;
	image* pokemonSelectBox;
	image* pokemonPageBg;
	image* route30bg;
	image* route30Limit;
	image* encounterWipe;

	RECT moveLimit;

	int count, bushCount, encounterCount;

	int optionNum;

	int pondIndex;
	int encounterIndex;

	bool isCollideLeft, isCollideRight, isCollideUp, isCollideDown;
	bool isShowRect;
	bool isOpenOption, isOpenPokemonPage;
	bool isOpenPokeball, isOpenFirstPokeBall, isOpenSecondPokeBall, isOpenThirdPokeBall;
	bool isAlreadySelected;
	bool isInBush;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void initImages();
	void playerMove();
	void normalPlayerMove();
	void villagePlayerMove();
	void labPlayerMove();
	void route30PlayerMove();
	void playerAnimation();
	void pondAnimation();
	void moveLocation();

	void checkInBush();
	void randomEncounter();

	void selectStartingPokemon();
	void selectingPokemon();
	void showPokemonSelectingPage();

	void openOption();
	void optionControl();
	void pokemonPageControl();
	void showPokemon();
	void showBag();

	void collisionCheck();
	void changeView();

	void savePlayerData();


};

