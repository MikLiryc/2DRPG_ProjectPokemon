#pragma once
#include "singletonBase.h"

class playerData : public singletonBase <playerData>
{
private:
	LOCATION location;
	DIRECTION direction;
	STATE state;

	RECT LT, LB, RT, RB, TL, TR, BL, BR;

	image* img;

	std::vector<tagPokemon> pokemonVector;

	float centerX, centerY, height, width;
	int moveLeftRight, moveUpDown;
	int playerAnimationCount, upDownIndex, leftRightIndex;

	bool isEncounter;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();
	void playerAnimation();

	std::vector<tagPokemon> getPlayerPokemon() { return pokemonVector; }
	void pushPokemon(tagPokemon pokemon, int hp, int level, int exp, int normalAtk, int normalDef, int specialAtk, int specialDef, int speed);
	void releasePokemon(int i);

	void addSkill(int pokemonVectorNum, TYPE type, SKILLTYPE skilltype, std::string name, int dmg, int maxPP, int prob);
	void addSkill(int pokemonVectorNum, int optionNum, TYPE type, SKILLTYPE skilltype, std::string name, int dmg, int maxPP, int prob);

	std::string getSkillName(int i) { return pokemonVector[0].skill[i].name; }

	int getLeftRightIndex() { return leftRightIndex; }
	int getUpDownIndex() { return upDownIndex; }
	int getMoveLeftRight() { return moveLeftRight; }
	int getMoveUpDown() { return moveUpDown; }

	void setMoveLeftRight(int num) { moveLeftRight = num; }
	void setMoveUpDown(int num) { moveUpDown = num; }

	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }
	float getHeight() { return height; }
	float getWidth() { return width; }

	void setCenterX(float num) { centerX = num; }
	void setCenterY(float num) { centerY = num; }

	BOOL getIsEncounter() { return isEncounter; }
	void setIsEncounter(bool a) { isEncounter = a; }

	RECT getLT() { return LT; }
	RECT getLB() { return LB; }
	RECT getRT() { return RT; }
	RECT getRB() { return RB; }
	RECT getTL() { return TL; }
	RECT getTR() { return TR; }
	RECT getBL() { return BL; }
	RECT getBR() { return BR; }

	image* getImg() { return img; }

	LOCATION getLocation() { return location; }
	void setLocation(LOCATION loc) { location = loc; }

	STATE getState() { return state; }
	void setState(STATE _state) { state = _state; }

	DIRECTION getDirection() { return direction; }
	void setDirection(DIRECTION dir) { direction = dir; }

};
