#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	initImages();

	count = 0;
	bushCount = 0;
	encounterCount = 0;
	encounterIndex = 0;
	optionNum = 0;

	pondIndex = 0;
	isShowRect = false;
	isCollideLeft = isCollideRight = isCollideUp = isCollideDown = false;

	isOpenOption = isOpenPokemonPage = false;
	isOpenPokeball = isOpenFirstPokeBall = isOpenSecondPokeBall = isOpenThirdPokeBall = false;
	isAlreadySelected = false;
	isInBush = false;

	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	if (!PLAYER->getIsEncounter())
	{
		PLAYER->update();

		if (INPUT->GetKeyDown(VK_TAB))
		{
			if (isShowRect)
			{
				isShowRect = false;
			}
			else if (!isShowRect)
			{
				isShowRect = true;
			}
		}
		if (INPUT->GetKeyDown(VK_F1))
		{
			PLAYER->pushPokemon(POKEMON->findPokemon("������"), 70, 5, 0, 15, 15, 20, 20, 4);
			PLAYER->addSkill(1, TYPE::�Ҳ�, SKILLTYPE::Ư��, "�Ҳɼ���", 40, 25, 100);
			PLAYER->addSkill(1, TYPE::��, SKILLTYPE::Ư��, "������", 40, 25, 100);
			PLAYER->addSkill(1, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
			PLAYER->addSkill(1, TYPE::����, SKILLTYPE::����, "���濡��", 100, 5, 80);
			PLAYER->pushPokemon(POKEMON->findPokemon("�ֻ�"), 150, 50, 0, 200, 80, 130, 60, 5);
			PLAYER->addSkill(2, TYPE::Ǯ, SKILLTYPE::����, "����ũ�ν�", 120, 15, 100);
			PLAYER->addSkill(2, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
			PLAYER->pushPokemon(POKEMON->findPokemon("����"), 70, 5, 0, 15, 15, 20, 20, 5);
			PLAYER->addSkill(3, TYPE::Ǯ, SKILLTYPE::����, "����ũ�ν�", 120, 15, 100);
			PLAYER->addSkill(3, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
			PLAYER->pushPokemon(POKEMON->findPokemon("��ö��"), 270, 51, 180, 280, 15, 20, 20, 5);
			PLAYER->addSkill(4, TYPE::Ǯ, SKILLTYPE::����, "����ũ�ν�", 120, 15, 100);
			PLAYER->addSkill(4, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
			PLAYER->pushPokemon(POKEMON->findPokemon("���ũ�ν�"), 250, 10, 11, 15, 52, 44, 20, 5);
			PLAYER->addSkill(5, TYPE::Ǯ, SKILLTYPE::����, "����ũ�ν�", 120, 15, 100);
			PLAYER->addSkill(5, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
		}
		if (INPUT->GetKeyDown(0x4F))
		{
			if (isOpenOption)
			{
				isOpenOption = false;
			}
			else if (!isOpenOption)
			{
				optionNum = 0;
				isOpenOption = true;
			}
		}
		if (INPUT->GetKeyDown(VK_LCONTROL))
		{
			SCENEMANAGER->loadScene("��Ʈ��");
		}
		if (!isOpenOption && !isOpenPokeball)
		{
			playerMove();
			if (PLAYER->getLocation() == LOCATION::STARTINGVILLIAGE)
			{
				pondAnimation();
			}
			if (PLAYER->getLocation() == LOCATION::POKELAB)
			{
				selectStartingPokemon();
			}
			if (PLAYER->getLocation() == LOCATION::ROUTE30)
			{
				randomEncounter();
			}
		}
		else if (isOpenOption && !isOpenPokemonPage)
		{
			optionControl();
		}
		else if (isOpenPokeball)
		{
			selectingPokemon();
		}
		else if (isOpenPokemonPage)
		{
			pokemonPageControl();
		}
		//std::cout << PLAYER->getCenterX() << "\t" << PLAYER->getCenterY() << "\t" << PLAYER->getMoveLeftRight() << "\t" << PLAYER->getMoveUpDown() << std::endl;
		//std::cout << PLAYER->getPlayerPokemon().size() << std::endl;
	}
	else if (PLAYER->getIsEncounter())
	{
		encounterCount++;
		if (encounterCount % 2 == 0)
		{
			encounterIndex++;
			if (encounterIndex > 26)
			{
				encounterIndex = 27;
				SCENEMANAGER->loadScene("����");
			}
		}
	}

}

void inGameScene::render()
{
	switch (PLAYER->getLocation())
	{
	case LOCATION::ROOM:
		goldRoomLimit->render(getMemDC(), 0, 0);
		collisionCheck();
		goldRoomBackground->render(getMemDC(), 0, 0);
		break;
	case LOCATION::GOLDHOUSEFIRSTFLOOR:
		goldHouseLimit->render(getMemDC(), 0, 0);
		collisionCheck();
		goldHouse->render(getMemDC(), 0, 0);
		break;
	case LOCATION::STARTINGVILLIAGE:
		villageLimit->render(getMemDC(), -1370 + PLAYER->getMoveLeftRight(), -255 + PLAYER->getMoveUpDown());
		collisionCheck();
		village->render(getMemDC(), -1370 + PLAYER->getMoveLeftRight(), -255 + PLAYER->getMoveUpDown());
		villagePond->frameRender(getMemDC(), 966 + PLAYER->getMoveLeftRight(), 345 + PLAYER->getMoveUpDown(), pondIndex, 0);
		break;
	case LOCATION::POKELAB:
		pokeLabLimit->render(getMemDC(), -325 + PLAYER->getMoveLeftRight(), -1040 + PLAYER->getMoveUpDown());
		collisionCheck();
		pokeLab->render(getMemDC(), -325 + PLAYER->getMoveLeftRight(), -1040 + PLAYER->getMoveUpDown());
		DrGongOverWorld->render(getMemDC(), 500 + PLAYER->getMoveLeftRight(), -525 + PLAYER->getMoveUpDown());
		for (int i = 0; i < 3; i++)
		{
			pokeBall->render(getMemDC(), 675 + 120 * i + PLAYER->getMoveLeftRight(), -500 + PLAYER->getMoveUpDown());
		}
		break;
	case LOCATION::SHOP:
		break;
	case LOCATION::POKECENTER:
		break;
	case LOCATION::ROUTE30:
		route30Limit->render(getMemDC(), -369 + PLAYER->getMoveLeftRight(), -2091 + PLAYER->getMoveUpDown());
		collisionCheck();
		checkInBush();
		route30bg->render(getMemDC(), -369 + PLAYER->getMoveLeftRight(), -2091 + PLAYER->getMoveUpDown());
		break;
	}
	changeView();
	playerAnimation();

	if (isOpenOption)
	{
		openOption();
	}
	if (isOpenPokeball)
	{
		showPokemonSelectingPage();
	}
	if (isOpenPokemonPage)
	{
		showPokemon();
	}
	if (PLAYER->getIsEncounter())
	{
		encounterWipe->frameRender(getMemDC(), -10, 0, encounterIndex, 0);
	}
}

void inGameScene::initImages()
{
	goldRoomLimit = IMAGEMANAGER->addImage("����ǹ�����", "images/goldRoomLimit.bmp", 900, 810);
	goldRoomBackground = IMAGEMANAGER->addImage("����ǹ�", "images/goldRoom.bmp", 900, 810, false);
	goldHouse = IMAGEMANAGER->addImage("�����1��", "images/goldHouseFirstFloor.bmp", 900, 810, false);
	goldHouseLimit = IMAGEMANAGER->addImage("�����1������", "images/goldHouseFirstFloorLimit.bmp", 900, 810, false);
	village = IMAGEMANAGER->addImage("���ʸ���", "images/village.bmp", 2811, 1794, false);
	villageLimit = IMAGEMANAGER->addImage("���ʸ�������", "images/villageLimit.bmp", 2811, 1794);
	villagePond = IMAGEMANAGER->addFrameImage("���ʸ���ȣ��", "images/villagePond.bmp", 1900, 394, 4, 1);
	pokeLab = IMAGEMANAGER->addImage("���ڻ翬����", "images/pokeLab.bmp", 1550, 1850);
	pokeLabLimit = IMAGEMANAGER->addImage("���ڻ翬��������", "images/pokeLabLimit.bmp", 1550, 1850);
	DrGongOverWorld = IMAGEMANAGER->addImage("���ڻ�", "images/DrGongOverWorld.bmp", 83, 95);
	pokeBall = IMAGEMANAGER->addImage("���Ϻ�", "images/pokeBall.bmp", 50, 50);
	pokemonSelectBox = IMAGEMANAGER->addImage("���ÿ�ڽ�", "images/���ÿ�ڽ�.bmp", 350, 350);
	pokemonPageBg = IMAGEMANAGER->addImage("���ϸ�������", "images/pokemonPage.bmp", 900, 810);
	route30bg = IMAGEMANAGER->addImage("30������", "images/route30.bmp", 2339, 2901);
	route30Limit = IMAGEMANAGER->addImage("30����������", "images/route30Limit.bmp", 2339, 2901);
	encounterWipe = IMAGEMANAGER->addFrameImage("��������", "images/EncounterWipe.bmp", 25555, 810, 28, 1);

	optionBox = IMAGEMANAGER->addImage("�ɼ�â", "images/optionBox.bmp", 300, 400);
	IMAGEMANAGER->addImage("SELECTARROW", "images/selectArrow.bmp", 50, 56);
	IMAGEMANAGER->addImage("TEXTBOX", "images/textBox.bmp", 900, 255);
}

void inGameScene::playerMove()
{
	switch (PLAYER->getLocation())
	{
	case ROOM:
		normalPlayerMove();
		break;
	case GOLDHOUSEFIRSTFLOOR:
		normalPlayerMove();
		break;
	case STARTINGVILLIAGE:
		villagePlayerMove();
		break;
	case POKELAB:
		labPlayerMove();
		break;
	case SHOP:
		break;
	case POKECENTER:
		break;
	case ROUTE30:
		route30PlayerMove();
		break;
	}
}

void inGameScene::normalPlayerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::LEFT);

		if (!isCollideLeft)
		{
			PLAYER->setCenterX(PLAYER->getCenterX() - 7);
		}
	}
	else if (INPUT->GetKey(VK_RIGHT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::RIGHT);

		if (!isCollideRight)
		{
			PLAYER->setCenterX(PLAYER->getCenterX() + 7);
		}
	}
	else if (INPUT->GetKey(VK_UP))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::UP);

		if (!isCollideUp)
		{
			PLAYER->setCenterY(PLAYER->getCenterY() - 7);
		}
	}
	else if (INPUT->GetKey(VK_DOWN))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::DOWN);

		if (!isCollideDown)
		{
			PLAYER->setCenterY(PLAYER->getCenterY() + 7);
		}
	}
	else
	{
		PLAYER->setState(STATE::IDLE);
	}
}

void inGameScene::villagePlayerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::LEFT);

		if (!isCollideLeft)
		{
			if (PLAYER->getCenterX() - 10 < WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() < 1370)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() + 7);
			}
			else if (PLAYER->getCenterX() > WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_RIGHT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::RIGHT);

		if (!isCollideRight)
		{
			if (PLAYER->getCenterX() + 10 > WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() > -540)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() - 7);
			}
			else if (PLAYER->getCenterX() < WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_UP))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::UP);

		if (!isCollideUp)
		{
			if (PLAYER->getCenterY() - 10 < WINSIZEY / 2
				&& PLAYER->getMoveUpDown() < 250)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() + 7);
			}
			else if (PLAYER->getCenterY() > WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_DOWN))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::DOWN);

		if (!isCollideDown)
		{
			if (PLAYER->getCenterY() + 10 > WINSIZEY / 2
				&& PLAYER->getMoveUpDown() > -720)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() - 7);
			}
			else if (PLAYER->getCenterY() < WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
		}
	}
	else
	{
		PLAYER->setState(STATE::IDLE);
	}
}

void inGameScene::labPlayerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::LEFT);

		if (!isCollideLeft)
		{
			if (PLAYER->getCenterX() - 10 < WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() < 325)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() + 7);
			}
			else if (PLAYER->getCenterX() > WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_RIGHT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::RIGHT);

		if (!isCollideRight)
		{
			if (PLAYER->getCenterX() + 10 > WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() > -325)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() - 7);
			}
			else if (PLAYER->getCenterX() < WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_UP))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::UP);

		if (!isCollideUp)
		{
			if (PLAYER->getCenterY() - 10 < WINSIZEY / 2
				&& PLAYER->getMoveUpDown() < 1040)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() + 7);
			}
			else if (PLAYER->getCenterY() > WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_DOWN))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::DOWN);

		if (!isCollideDown)
		{
			if (PLAYER->getCenterY() + 10 > WINSIZEY / 2
				&& PLAYER->getMoveUpDown() > -20)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() - 7);
			}
			else if (PLAYER->getCenterY() < WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
		}
	}
	else
	{
		PLAYER->setState(STATE::IDLE);
	}
}

void inGameScene::route30PlayerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::LEFT);

		if (!isCollideLeft)
		{
			if (PLAYER->getCenterX() - 10 < WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() < 370)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() + 7);
			}
			else if (PLAYER->getCenterX() > WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_RIGHT))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::RIGHT);

		if (!isCollideRight)
		{
			if (PLAYER->getCenterX() + 10 > WINSIZEX / 2
				&& PLAYER->getMoveLeftRight() > -1060)
			{
				PLAYER->setMoveLeftRight(PLAYER->getMoveLeftRight() - 7);
			}
			else if (PLAYER->getCenterX() < WINSIZEX / 2)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
			else
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_UP))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::UP);

		if (!isCollideUp)
		{
			if (PLAYER->getCenterY() - 10 < WINSIZEY / 2
				&& PLAYER->getMoveUpDown() < 2070)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() + 7);
			}
			else if (PLAYER->getCenterY() > WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - 7);
			}
		}
	}
	else if (INPUT->GetKey(VK_DOWN))
	{
		PLAYER->setState(STATE::RUN);
		PLAYER->setDirection(DIRECTION::DOWN);

		if (!isCollideDown)
		{
			if (PLAYER->getCenterY() + 10 > WINSIZEY / 2
				&& PLAYER->getMoveUpDown() > 0)
			{
				PLAYER->setMoveUpDown(PLAYER->getMoveUpDown() - 7);
			}
			else if (PLAYER->getCenterY() < WINSIZEY / 2)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
			else
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + 7);
			}
		}
	}
	else
	{
		PLAYER->setState(STATE::IDLE);
	}
}

void inGameScene::playerAnimation()
{
	if (PLAYER->getState() == STATE::RUN)
	{
		switch (PLAYER->getDirection())
		{
		case DIRECTION::LEFT:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				PLAYER->getLeftRightIndex(), 1);
			break;
		case DIRECTION::RIGHT:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				PLAYER->getLeftRightIndex(), 0);
			break;
		case DIRECTION::UP:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				PLAYER->getUpDownIndex(), 2);
			break;
		case DIRECTION::DOWN:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				PLAYER->getUpDownIndex(), 3);
			break;
		}
	}
	else if (PLAYER->getState() == STATE::IDLE)
	{
		switch (PLAYER->getDirection())
		{
		case DIRECTION::LEFT:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				0,
				1);
			break;
		case DIRECTION::RIGHT:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				0,
				0);
			break;
		case DIRECTION::UP:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				0,
				2);
			break;
		case DIRECTION::DOWN:
			PLAYER->getImg()->frameRender
			(getMemDC(),
				PLAYER->getCenterX() - PLAYER->getWidth() / 2,
				PLAYER->getCenterY() - PLAYER->getHeight() / 2,
				0,
				3);
			break;
		}
	}
}

void inGameScene::pondAnimation()
{
	count++;
	if (count % 20 == 0)
	{
		pondIndex++;
		if (pondIndex > 3)
		{
			pondIndex = 0;
		}
	}
}

void inGameScene::moveLocation()
{
	switch (PLAYER->getLocation())
	{
	case LOCATION::ROOM:
		if (GetPixel(getMemDC(), PLAYER->getTL().left + 5, PLAYER->getTL().top + 5) == RGB(0, 0, 255)
			|| GetPixel(getMemDC(), PLAYER->getTR().left + 5, PLAYER->getTR().top + 5) == RGB(0, 0, 255)) {
			PLAYER->setCenterX(837);
			PLAYER->setCenterY(200);
			PLAYER->setLocation(LOCATION::GOLDHOUSEFIRSTFLOOR);
			PLAYER->setDirection(DIRECTION::DOWN);
			PLAYER->setState(STATE::IDLE);
			std::cout << "move to First Floor" << std::endl;
		}
		break;
	case LOCATION::GOLDHOUSEFIRSTFLOOR:
		if (GetPixel(getMemDC(), PLAYER->getTL().left + 5, PLAYER->getTL().top + 5) == RGB(0, 0, 255)
			|| GetPixel(getMemDC(), PLAYER->getTR().left + 5, PLAYER->getTR().top + 5) == RGB(0, 0, 255))
		{
			PLAYER->setCenterX(800);
			PLAYER->setCenterY(250);
			PLAYER->setLocation(LOCATION::ROOM);
			PLAYER->setDirection(DIRECTION::DOWN);
			PLAYER->setState(STATE::IDLE);
			std::cout << "move to Room" << std::endl;
		}
		if (GetPixel(getMemDC(), PLAYER->getBL().left + 5, PLAYER->getBL().top + 5) == RGB(0, 255, 0)
			|| GetPixel(getMemDC(), PLAYER->getBR().left + 5, PLAYER->getBR().top + 5) == RGB(0, 255, 0))
		{
			PLAYER->setCenterX(WINSIZEX / 2);
			PLAYER->setCenterY(WINSIZEY / 2);
			PLAYER->setLocation(LOCATION::STARTINGVILLIAGE);
			PLAYER->setDirection(DIRECTION::DOWN);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(0);
			PLAYER->setMoveUpDown(0);
			std::cout << "move to Village" << std::endl;
		}
		break;
	case LOCATION::STARTINGVILLIAGE:
		if (GetPixel(getMemDC(), PLAYER->getTL().left + 5, PLAYER->getTL().top + 5) == RGB(0, 0, 255)
			|| GetPixel(getMemDC(), PLAYER->getTR().left + 5, PLAYER->getTR().top + 5) == RGB(0, 0, 255))
		{
			PLAYER->setCenterX(580);
			PLAYER->setCenterY(680);
			PLAYER->setLocation(LOCATION::GOLDHOUSEFIRSTFLOOR);
			PLAYER->setDirection(DIRECTION::UP);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(0);
			PLAYER->setMoveUpDown(0);
			std::cout << "move to House" << std::endl;
		}
		if (GetPixel(getMemDC(), PLAYER->getTL().left + 5, PLAYER->getTL().top + 5) == RGB(0, 0, 254)
			|| GetPixel(getMemDC(), PLAYER->getTR().left + 5, PLAYER->getTR().top + 5) == RGB(0, 0, 254))
		{
			PLAYER->setCenterX(450);
			PLAYER->setCenterY(650);
			PLAYER->setLocation(LOCATION::POKELAB);
			PLAYER->setDirection(DIRECTION::UP);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(0);
			PLAYER->setMoveUpDown(0);
			std::cout << "move to Lab" << std::endl;
		}
		if (GetPixel(getMemDC(), PLAYER->getLT().left + 5, PLAYER->getLT().top + 5) == RGB(0, 255, 0)
			|| GetPixel(getMemDC(), PLAYER->getLB().left + 5, PLAYER->getLB().top + 5) == RGB(0, 255, 0))
		{
			PLAYER->setCenterX(450);
			PLAYER->setCenterY(730);
			PLAYER->setLocation(LOCATION::ROUTE30);
			PLAYER->setDirection(DIRECTION::UP);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(0);
			PLAYER->setMoveUpDown(0);
			std::cout << "move to Route 30" << std::endl;
		}
		break;
	case LOCATION::POKELAB:
		if (GetPixel(getMemDC(), PLAYER->getBL().left + 5, PLAYER->getBL().top + 5) == RGB(0, 255, 0)
			|| GetPixel(getMemDC(), PLAYER->getBR().left + 5, PLAYER->getBR().top + 5) == RGB(0, 255, 0))
		{
			PLAYER->setCenterX(450);
			PLAYER->setCenterY(405);
			PLAYER->setLocation(LOCATION::STARTINGVILLIAGE);
			PLAYER->setDirection(DIRECTION::DOWN);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(833);
			PLAYER->setMoveUpDown(203);
			std::cout << "move to Village" << std::endl;
		}
		break;
	case LOCATION::SHOP:
		break;
	case LOCATION::POKECENTER:
		break;
	case LOCATION::ROUTE30:
		if (GetPixel(getMemDC(), PLAYER->getBL().left + 5, PLAYER->getBL().top + 5) == RGB(0, 0, 255)
			|| GetPixel(getMemDC(), PLAYER->getBR().left + 5, PLAYER->getBR().top + 5) == RGB(0, 0, 255))
		{
			PLAYER->setCenterX(135);
			PLAYER->setCenterY(405);
			PLAYER->setLocation(LOCATION::STARTINGVILLIAGE);
			PLAYER->setDirection(DIRECTION::RIGHT);
			PLAYER->setState(STATE::IDLE);
			PLAYER->setMoveLeftRight(1372);
			PLAYER->setMoveUpDown(-231);
			std::cout << "move to Village" << std::endl;
		}
		break;
	}
}

void inGameScene::checkInBush()
{
	if (GetPixel(getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) == RGB(0, 255, 0))
	{
		isInBush = true;
		std::cout << bushCount << "\t" << PLAYER->getIsEncounter() << "\t" << isInBush << std::endl;
	}
	else
	{
		isInBush = false;
		std::cout << bushCount << "\t" << PLAYER->getIsEncounter() << "\t" << isInBush << std::endl;
	}
}

void inGameScene::randomEncounter()
{
	if (isInBush && !PLAYER->getIsEncounter())
	{
		bushCount++;
		if (bushCount % 50 == 0)
		{
			int rand = RND->range(10);
			if (rand < 2)
			{
				PLAYER->setIsEncounter(true);
			}
		}
	}
}

void inGameScene::selectStartingPokemon()
{
	if (INPUT->GetKeyDown(VK_RETURN) && !isAlreadySelected)
	{
		if (PLAYER->getMoveLeftRight() < -230 && PLAYER->getMoveLeftRight() > -280
			&& PLAYER->getMoveUpDown() < 750 && PLAYER->getMoveUpDown() > 740)
		{
			optionNum = 0;
			isOpenPokeball = true;
			isOpenFirstPokeBall = true;
		}
		if (PLAYER->getMoveLeftRight() < -320 && PLAYER->getCenterX() < 570)
		{
			optionNum = 0;
			isOpenPokeball = true;
			isOpenSecondPokeBall = true;
		}
		if (PLAYER->getMoveLeftRight() < -320 && PLAYER->getCenterX() > 590
			&& PLAYER->getCenterX() < 650)
		{
			optionNum = 0;
			isOpenPokeball = true;
			isOpenThirdPokeBall = true;
		}
	}
}

void inGameScene::selectingPokemon()
{
	if (INPUT->GetKeyDown(VK_LEFT) && optionNum > 0)
	{
		optionNum--;
	}
	if (INPUT->GetKeyDown(VK_RIGHT) && optionNum < 1)
	{
		optionNum++;
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		switch (optionNum)
		{
		case 0:
			if (isOpenFirstPokeBall)
			{
				PLAYER->pushPokemon(POKEMON->findPokemon("������"), 70, 5, 0, 15, 15, 20, 20, 5);
				PLAYER->addSkill(0, TYPE::�Ҳ�, SKILLTYPE::Ư��, "�Ҳɼ���", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::��, SKILLTYPE::Ư��, "������", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
				PLAYER->addSkill(0, TYPE::����, SKILLTYPE::����, "���濡��", 100, 5, 80);
				isAlreadySelected = true;
				isOpenPokeball = false;
				isOpenFirstPokeBall = false;
				std::cout << PLAYER->getPlayerPokemon()[0].skill.size() << std::endl;
				std::cout << PLAYER->getSkillName(0) << "\t" << PLAYER->getSkillName(1) << "\t" <<
					PLAYER->getSkillName(2) << "\t" << PLAYER->getSkillName(3) << "\t" << std::endl;
			}
			else if (isOpenSecondPokeBall)
			{
				PLAYER->pushPokemon(POKEMON->findPokemon("������"), 70, 5, 0, 15, 15, 20, 20, 4);
				PLAYER->addSkill(0, TYPE::�Ҳ�, SKILLTYPE::Ư��, "�Ҳɼ���", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::��, SKILLTYPE::Ư��, "������", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
				PLAYER->addSkill(0, TYPE::����, SKILLTYPE::����, "���濡��", 100, 5, 80);
				isAlreadySelected = true;
				isOpenPokeball = false;
				isOpenSecondPokeBall = false;
				std::cout << PLAYER->getPlayerPokemon()[0].skill.size() << std::endl;
				std::cout << PLAYER->getSkillName(0) << "\t" << PLAYER->getSkillName(1) << "\t" <<
					PLAYER->getSkillName(2) << "\t" << PLAYER->getSkillName(3) << "\t" << std::endl;
			}
			else if (isOpenThirdPokeBall)
			{
				PLAYER->pushPokemon(POKEMON->findPokemon("ġ�ڸ�Ÿ"), 70, 5, 0, 15, 15, 20, 20, 4.5);
				PLAYER->addSkill(0, TYPE::�Ҳ�, SKILLTYPE::Ư��, "�Ҳɼ���", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::��, SKILLTYPE::Ư��, "������", 40, 25, 100);
				PLAYER->addSkill(0, TYPE::Ǯ, SKILLTYPE::����, "�ٳ�������", 55, 25, 95);
				PLAYER->addSkill(0, TYPE::����, SKILLTYPE::����, "���濡��", 100, 5, 80);
				isAlreadySelected = true;
				isOpenPokeball = false;
				isOpenThirdPokeBall = false;
				std::cout << PLAYER->getPlayerPokemon()[0].skill.size() << std::endl;
				std::cout << PLAYER->getSkillName(0) << "\t" << PLAYER->getSkillName(1) << "\t" <<
					PLAYER->getSkillName(2) << "\t" << PLAYER->getSkillName(3) << "\t" << std::endl;
			}
			break;
		case 1:
			if (isOpenFirstPokeBall)
			{
				isOpenPokeball = false;
				isOpenFirstPokeBall = false;
			}
			else if (isOpenSecondPokeBall)
			{
				isOpenPokeball = false;
				isOpenSecondPokeBall = false;
			}
			else if (isOpenThirdPokeBall)
			{
				isOpenPokeball = false;
				isOpenThirdPokeBall = false;
			}
			break;
		}
	}
}

void inGameScene::showPokemonSelectingPage()
{
	if (isOpenFirstPokeBall)
	{
		IMAGEMANAGER->findImage("TEXTBOX")->render(getMemDC(), 0, 550);
		pokemonSelectBox->render(getMemDC(), WINSIZEX / 2 - 175, WINSIZEY / 2 - 240);
		IMAGEMANAGER->findImage("������")->render(getMemDC(), WINSIZEX / 2 - 135, WINSIZEY / 2 - 200, 270, 0, 270, 270);

		IMAGEMANAGER->findImage("SELECTARROW")->render(getMemDC(), 20 + optionNum * 170, 700);

		SetBkMode(getMemDC(), TRANSPARENT);
		RECT textDrawBox = RectMakeCenter(WINSIZEX / 2, 700, 830, 200);
		HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		char str[128];
		sprintf_s(str, "���������� ���ұ�?\n\n     ��       �ƴϿ�");
		DrawText(getMemDC(), str, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}
	else if (isOpenSecondPokeBall)
	{
		IMAGEMANAGER->findImage("TEXTBOX")->render(getMemDC(), 0, 550);
		pokemonSelectBox->render(getMemDC(), WINSIZEX / 2 - 175, WINSIZEY / 2 - 240);
		IMAGEMANAGER->findImage("������")->render(getMemDC(), WINSIZEX / 2 - 135, WINSIZEY / 2 - 200, 270, 0, 270, 270);

		IMAGEMANAGER->findImage("SELECTARROW")->render(getMemDC(), 20 + optionNum * 170, 700);

		SetBkMode(getMemDC(), TRANSPARENT);
		RECT textDrawBox = RectMakeCenter(WINSIZEX / 2, 700, 830, 200);
		HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		char str[128];
		sprintf_s(str, "�����ڷ� ���ұ�?\n\n     ��       �ƴϿ�");
		DrawText(getMemDC(), str, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}
	else if (isOpenThirdPokeBall)
	{
		IMAGEMANAGER->findImage("TEXTBOX")->render(getMemDC(), 0, 550);
		pokemonSelectBox->render(getMemDC(), WINSIZEX / 2 - 175, WINSIZEY / 2 - 240);
		IMAGEMANAGER->findImage("ġ�ڸ�Ÿ")->render(getMemDC(), WINSIZEX / 2 - 135, WINSIZEY / 2 - 200, 270, 0, 270, 270);

		IMAGEMANAGER->findImage("SELECTARROW")->render(getMemDC(), 20 + optionNum * 170, 700);

		SetBkMode(getMemDC(), TRANSPARENT);
		RECT textDrawBox = RectMakeCenter(WINSIZEX / 2, 700, 830, 200);
		HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		char str[128];
		sprintf_s(str, "ġ�ڸ�Ÿ�� ���ұ�?\n\n     ��       �ƴϿ�");
		DrawText(getMemDC(), str, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}
}

void inGameScene::collisionCheck()
{
	//���� �� ����Ʈ�� ������ �ɸ��� ���� �浹
	if (GetPixel(getMemDC(), PLAYER->getLT().left + 5, PLAYER->getLT().top + 5) == RGB(255, 0, 0)
		|| GetPixel(getMemDC(), PLAYER->getLB().left + 5, PLAYER->getLB().top + 5) == RGB(255, 0, 0)) {
		isCollideLeft = true;
	}
	else { isCollideLeft = false; }

	//������ �� ����Ʈ�� ������ �ɸ��� ������ �浹
	if (GetPixel(getMemDC(), PLAYER->getRT().left + 5, PLAYER->getRT().top + 5) == RGB(255, 0, 0)
		|| GetPixel(getMemDC(), PLAYER->getRB().left + 5, PLAYER->getRB().top + 5) == RGB(255, 0, 0)) {
		isCollideRight = true;
	}
	else { isCollideRight = false; }

	//���� �� ����Ʈ�� ������ �ɸ��� ���� �浹
	if (GetPixel(getMemDC(), PLAYER->getTL().left + 5, PLAYER->getTL().top + 5) == RGB(255, 0, 0)
		|| GetPixel(getMemDC(), PLAYER->getTR().left + 5, PLAYER->getTR().top + 5) == RGB(255, 0, 0)) {
		isCollideUp = true;
	}
	else { isCollideUp = false; }

	//�Ʒ��� �� ����Ʈ�� ������ �ɸ��� �Ʒ��� �浹
	if (GetPixel(getMemDC(), PLAYER->getBL().left + 5, PLAYER->getBL().top + 5) == RGB(255, 0, 0)
		|| GetPixel(getMemDC(), PLAYER->getBR().left + 5, PLAYER->getBR().top + 5) == RGB(255, 0, 0)) {
		isCollideDown = true;
	}
	else { isCollideDown = false; }

	//��Ż �� (�ʷ�/ �Ķ�) �ɸ��� �� �̵�
	moveLocation();
}

void inGameScene::changeView()
{
	if (isShowRect)
	{
		switch (PLAYER->getLocation())
		{
		case LOCATION::ROOM:
			goldRoomLimit->render(getMemDC(), 0, 0);
			break;
		case LOCATION::GOLDHOUSEFIRSTFLOOR:
			goldHouseLimit->render(getMemDC(), 0, 0);
			break;
		case LOCATION::STARTINGVILLIAGE:
			villageLimit->render(getMemDC(), -1370 + PLAYER->getMoveLeftRight(), -255 + PLAYER->getMoveUpDown());
			break;
		case LOCATION::POKELAB:
			pokeLabLimit->render(getMemDC(), -325 + PLAYER->getMoveLeftRight(), -1040 + PLAYER->getMoveUpDown());
			break;
		case LOCATION::SHOP:
			break;
		case LOCATION::POKECENTER:
			break;
		case LOCATION::ROUTE30:
			route30Limit->render(getMemDC(), -369 + PLAYER->getMoveLeftRight(), -2091 + PLAYER->getMoveUpDown());
			break;
		}
		Rectangle(getMemDC(), PLAYER->getLT());
		Rectangle(getMemDC(), PLAYER->getLB());
		Rectangle(getMemDC(), PLAYER->getRT());
		Rectangle(getMemDC(), PLAYER->getRB());
		Rectangle(getMemDC(), PLAYER->getTL());
		Rectangle(getMemDC(), PLAYER->getTR());
		Rectangle(getMemDC(), PLAYER->getBL());
		Rectangle(getMemDC(), PLAYER->getBR());
	}
}

void inGameScene::optionControl()
{
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (optionNum > 0)
		{
			optionNum--;
		}
	}
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (optionNum < 3)
		{
			optionNum++;
		}
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		switch (optionNum)
		{
		case 0:
			optionNum = 0;
			isOpenPokemonPage = true;
			break;
		case 1:

			break;
		case 2:
			savePlayerData();
			break;
		case 3:
			PostQuitMessage(0);
			break;
		}
	}

}

void inGameScene::pokemonPageControl()
{
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (optionNum > 0)
		{
			optionNum--;
		}
	}
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (optionNum < PLAYER->getPlayerPokemon().size() - 1)
		{
			optionNum++;
		}
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		PLAYER->releasePokemon(optionNum);
		if (optionNum == 0)
		{
			optionNum = 0;
		}
		else
		{
			optionNum -= 1;
		}
	}
	if (INPUT->GetKeyDown(VK_BACK))
	{
		isOpenPokemonPage = false;
		optionNum = 0;
	}
}

void inGameScene::showPokemon()
{
	pokemonPageBg->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("SELECTARROW")->render(getMemDC(), 30, 65 + 70 * optionNum);
	for (int i = 0; i < PLAYER->getPlayerPokemon().size(); i++)
	{
		RECT textBox = RectMake(80, 80 + 70 * i, 300, 50);
		RECT StatusBox = RectMake(300, 80, 700, 500);
		char str[512];
		char type[128];
		char secType[128];

		SetBkMode(getMemDC(), TRANSPARENT);
		HFONT myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		sprintf_s(str, PLAYER->getPlayerPokemon()[i].name.c_str());
		DrawText(getMemDC(), str, -1, &textBox, DT_LEFT | DT_VCENTER);

		switch (PLAYER->getPlayerPokemon()[optionNum].primarytype)
		{
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::�븻:
			sprintf_s(type, "�븻");
			break;
		case TYPE::�Ҳ�:
			sprintf_s(type, "�Ҳ�");
			break;
		case TYPE::��:
			sprintf_s(type, "��");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::Ǯ:
			sprintf_s(type, "Ǯ");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::��:
			sprintf_s(type, "��");
			break;
		case TYPE::��:
			sprintf_s(type, "��");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::������:
			sprintf_s(type, "������");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::����:
			sprintf_s(type, "����");
			break;
		case TYPE::��Ʈ:
			sprintf_s(type, "��Ʈ");
			break;
		case TYPE::�巡��:
			sprintf_s(type, "�巡��");
			break;
		case TYPE::��:
			sprintf_s(type, "��");
			break;
		case TYPE::��ö:
			sprintf_s(type, "��ö");
			break;
		}
		switch (PLAYER->getPlayerPokemon()[optionNum].secondaryType)
		{
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::�븻:
			sprintf_s(secType, "�븻");
			break;
		case TYPE::�Ҳ�:
			sprintf_s(secType, "�Ҳ�");
			break;
		case TYPE::��:
			sprintf_s(secType, "��");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::Ǯ:
			sprintf_s(secType, "Ǯ");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::��:
			sprintf_s(secType, "��");
			break;
		case TYPE::��:
			sprintf_s(secType, "��");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::������:
			sprintf_s(secType, "������");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::����:
			sprintf_s(secType, "����");
			break;
		case TYPE::��Ʈ:
			sprintf_s(secType, "��Ʈ");
			break;
		case TYPE::�巡��:
			sprintf_s(secType, "�巡��");
			break;
		case TYPE::��:
			sprintf_s(secType, "��");
			break;
		case TYPE::��ö:
			sprintf_s(secType, "��ö");
			break;
		}

		sprintf_s(str, " Lv : %d \n HP : %d \n Norm. ATK : %d \n Norm. DEF : %d \n Spc. ATK : %d \n Spc. DEF : %d \n Speed : %d \n TYPE : %s \n SEC. TYPE : %s",
			PLAYER->getPlayerPokemon()[optionNum].level,
			PLAYER->getPlayerPokemon()[optionNum].hp,
			PLAYER->getPlayerPokemon()[optionNum].normalAtk,
			PLAYER->getPlayerPokemon()[optionNum].normalDef,
			PLAYER->getPlayerPokemon()[optionNum].specialAtk,
			PLAYER->getPlayerPokemon()[optionNum].specialDef,
			PLAYER->getPlayerPokemon()[optionNum].speed,
			type,
			secType);

		DrawText(getMemDC(), str, -1, &StatusBox, DT_LEFT | DT_VCENTER);

		sprintf_s(str, PLAYER->getPlayerPokemon()[i].name.c_str());
		DrawText(getMemDC(), str, -1, &textBox, DT_LEFT | DT_VCENTER);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		PLAYER->getPlayerPokemon()[optionNum].img->render(getMemDC(), 594, 79, 0, 0, 270, 270);
	}
}

void inGameScene::showBag()
{
}

void inGameScene::savePlayerData()
{
	char centerX[128];
	char centerY[128];
	char LeftRight[128];
	char UpDown[128];
	char Location[128];
	char Direction[128];
	char moveLeftRight[128];
	char moveUpDown[128];

	INIDATA->addData("CURRENTSCENE", "SCENE", "inGameScene");

	sprintf_s(centerX, "%f", PLAYER->getCenterX());
	INIDATA->addData("PLAYER", "centerX", centerX);
	sprintf_s(centerY, "%f", PLAYER->getCenterY());
	INIDATA->addData("PLAYER", "centerY", centerY);

	sprintf_s(Location, "%d", PLAYER->getLocation());
	INIDATA->addData("PLAYER", "LOCATION", Location);

	sprintf_s(Direction, "%d", PLAYER->getDirection());
	INIDATA->addData("PLAYER", "DIRECTION", Direction);

	sprintf_s(LeftRight, "%d", PLAYER->getMoveLeftRight());
	INIDATA->addData("CAMERA", "moveLeftRight", LeftRight);
	sprintf_s(UpDown, "%d", PLAYER->getMoveUpDown());
	INIDATA->addData("CAMERA", "moveUpDown", UpDown);

	INIDATA->saveINI("data/playerData");
}

void inGameScene::openOption()
{
	if (isOpenOption)
	{
		optionBox->render(getMemDC(), 600, 0);
		IMAGEMANAGER->findImage("SELECTARROW")->render(getMemDC(), 620, 65 + 70 * optionNum);
	}
}
