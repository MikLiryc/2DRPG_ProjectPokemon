#pragma once
#include "gameNode.h"

class battleScene : public gameNode
{
private:
	image* battleSceneBg;
	image* selectArrow;
	image* pokemonPageBg;

	int alpha;
	int enemyAlpha;
	int optionNum;
	int currentPokemonNum;

	tagPokemon enemy;

	bool isSelectAction, isSelectPokemon, isSelectSkill;
	bool isPlayerTurn, isEnemyTurn;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void initImages();

	void optionControl();
	void selectAction();
	void showOption();

	void attack(int num);
	void showSkill();
	void skillOptionControl();

	void enemyAttack();

	void pokemon();
	void showPokemon();
	void pokemonOptionControl();

	void bag();

	void run();

	void selectPokemon();

};

