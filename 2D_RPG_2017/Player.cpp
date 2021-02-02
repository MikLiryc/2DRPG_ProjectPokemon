#include "stdafx.h"
#include "Player.h"

HRESULT playerData::init()
{
	img = IMAGEMANAGER->addFrameImage("°ñµåSD", "images/goldOverWorld.bmp", 285, 400, 3, 4);
	location = LOCATION::ROOM;
	direction = DIRECTION::DOWN;
	state = STATE::IDLE;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;
	width = 95;
	height = 100;
	leftRightIndex = upDownIndex = 0;
	moveLeftRight = moveUpDown = 0;

	isEncounter = false;

	playerAnimationCount = 0;
	return S_OK;
}

void playerData::release()
{
}

void playerData::update()
{
	LT = RectMakeCenter(centerX - width / 2, centerY + 25, 10, 10);
	LB = RectMakeCenter(centerX - width / 2, centerY - 25, 10, 10);
	RT = RectMakeCenter(centerX + width / 2, centerY + 25, 10, 10);
	RB = RectMakeCenter(centerX + width / 2, centerY - 25, 10, 10);
	TL = RectMakeCenter(centerX - 20, centerY - height / 2, 10, 10);
	TR = RectMakeCenter(centerX + 20, centerY - height / 2, 10, 10);
	BL = RectMakeCenter(centerX - 20, centerY + height / 2, 10, 10);
	BR = RectMakeCenter(centerX + 20, centerY + height / 2, 10, 10);

	playerAnimation();
}

void playerData::render()
{

}

void playerData::playerMove()
{
}

void playerData::playerAnimation()
{
	playerAnimationCount++;
	if (playerAnimationCount % 10 == 0)
	{
		leftRightIndex++;
		upDownIndex++;
		if (leftRightIndex > 1)
		{
			leftRightIndex = 0;
		}
		if (upDownIndex > 2)
		{
			upDownIndex = 1;
		}
		playerAnimationCount = 0;
	}
}

void playerData::pushPokemon(tagPokemon pokemon, int hp, int level, int exp, int normalAtk, int normalDef, int specialAtk, int specialDef, int speed)
{
	if (pokemonVector.size() < 6)
	{
		tagPokemon temp = pokemon;
		temp.hp = hp;
		temp.level = level;
		temp.exp = exp;
		temp.normalAtk = normalAtk;
		temp.normalDef = normalDef;
		temp.specialAtk = specialAtk;
		temp.specialDef = specialDef;
		temp.speed = speed;

		pokemonVector.push_back(temp);
	}
}

void playerData::releasePokemon(int i)
{
	if (pokemonVector[i].img != nullptr)
	{
		pokemonVector.erase(pokemonVector.begin() + i);
	}
}

void playerData::addSkill(int pokemonVectorNum, TYPE type, SKILLTYPE skilltype, std::string name, int dmg, int maxPP, int prob)
{
	tagSkill temp;
	temp.type = type;
	temp.skillType = skilltype;
	temp.name = name;
	temp.damage = dmg;
	temp.maxPp = maxPP;
	temp.currentPP = maxPP;
	temp.prob = prob;

	pokemonVector[pokemonVectorNum].skill.push_back(temp);
	std::cout << "skill push back!" << std::endl;
}

void playerData::addSkill(int pokemonVectorNum, int optionNum, TYPE type, SKILLTYPE skilltype, std::string name, int dmg, int maxPP, int prob)
{
	if (this->getPlayerPokemon()[pokemonVectorNum].skill.size() > 3)
	{
		tagSkill temp;
		temp.type = type;
		temp.skillType = skilltype;
		temp.name = name;
		temp.damage = dmg;
		temp.maxPp = maxPP;
		temp.currentPP = maxPP;
		temp.prob = prob;

		pokemonVector[pokemonVectorNum].skill.erase(pokemonVector[pokemonVectorNum].skill.begin() + optionNum);
		pokemonVector[pokemonVectorNum].skill.push_back(temp);
		std::cout << "skill push back!" << std::endl;
	}
	else
	{
		this->addSkill(pokemonVectorNum, type, skilltype, name, dmg, maxPP, prob);
	}
}


