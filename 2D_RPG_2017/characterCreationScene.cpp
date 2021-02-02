#include "stdafx.h"
#include "characterCreationScene.h"

HRESULT characterCreationScene::init()
{
	startTextBoxImg = IMAGEMANAGER->addImage("STARTTEXTBOX", "images/starttextBox.bmp", 450, 200);
	textBoxImg = IMAGEMANAGER->addImage("TEXTBOX", "images/textBox.bmp", 900, 255);
	nameSelectBoxImg = IMAGEMANAGER->addImage("SELECTNAME", "images/characterNameBox.bmp", 250, 400);
	backgroundImg = IMAGEMANAGER->addImage("CHARACTERCREATIONBACKGROUND", "images/characterCreationBackground.bmp", WINSIZEX, WINSIZEY);
	selectArrowImg = IMAGEMANAGER->addImage("SELECTARROW", "images/selectArrow.bmp", 50, 56);
	downArrowImg = IMAGEMANAGER->addImage("DOWNARROW", "images/downArrow.bmp", 56, 50);
	DrOhImg = IMAGEMANAGER->addFrameImage("Dr.OH", "images/DrOh.bmp", 2286, 400, 8, 1);
	marilImg = IMAGEMANAGER->addFrameImage("MARIL", "images/maril.bmp", 1000, 200, 5, 1);
	goldImg = IMAGEMANAGER->addFrameImage("GOLD", "images/goldBecomeOverWorld.bmp", 3428, 400, 12, 1);
	textDrawBox = RectMakeCenter(WINSIZEX / 2, 730, 830, 200);

	setText("texts/DrOhLines.txt");

	textLineNum = count = selectCount = nameSelectCount = 0;
	goldIndex = DrOhIndex = MarilIndex = 0;
	isStart = false;
	isResumeText = false;
	isShowDrOh = isDrOhFadeIn = isDrOhFadeOut = false;
	isStartNameSelection = isShowGold = isGoldTurnSD = false;
	isShowMaril = isMarilFadeOut = isMarilFadeIn = false;
	isSelectName = false;


	return S_OK;
}

void characterCreationScene::release()
{
}

void characterCreationScene::update()
{
	if (!isStart)
	{
		selectArrowMove();

		if (INPUT->GetKeyDown(VK_RETURN))
		{
			switch (selectCount)
			{
			case 0:
				isStart = true;
				isShowDrOh = true;
				isDrOhFadeIn = true;
				break;
			case 1:
				loadPlayer();
				break;
			}
		}
	}
	else if (isStart)
	{
		count++;
		if (isShowDrOh)
		{
			DrOhAnimation();
			MarilAnimation();
			resumeText();
		}
		else if (isShowGold)
		{
			if (isStartNameSelection)
			{
				setText("texts/characterNameSelectionLines.txt");
				nameSelectCount = 0;
				textLineNum = 0;
				isSelectName = true;
				isStartNameSelection = false;
			}
			if (isSelectName)
			{
				savePlayer();
				selectArrowMove();
			}
			if (!isSelectName)
			{
				resumeText();
			}
			goldAnimation();
			if (goldIndex > 11)
			{
				SCENEMANAGER->loadScene("ÀÎ°ÔÀÓ");
			}
		}
	}
}

void characterCreationScene::render()
{
	backgroundImg->render(getMemDC(), 0, 0);
	if (!isStart)
	{
		startTextBoxImg->render(getMemDC(), 0, 40);
		selectArrowImg->render(getMemDC(), 10, 72 + 79 * selectCount);
	}
	else if (isStart)
	{
		if (isShowDrOh)
		{
			DrOhImg->frameRender(getMemDC(), 450 - 143, 350 - 230, DrOhIndex, 0);
			if (DrOhIndex == 4)
			{
				textBoxImg->render(getMemDC(), 0, 550);
				textOut();
				if (!isResumeText)
				{
					downArrowImg->render(getMemDC(), 760, 740);
				}
				if (isShowMaril)
				{
					marilImg->frameRender(getMemDC(), 130, 330, MarilIndex, 0);
				}
			}
		}
		std::cout << DrOhIndex << "\t" << MarilIndex << std::endl;
		if (isShowGold)
		{
			goldImg->frameRender(getMemDC(), 450 - 143, 350 - 230, goldIndex, 0);
			if (goldIndex == 5)
			{
				if (isSelectName)
				{
					nameSelectBoxImg->render(getMemDC(), 0, 40);
					selectArrowImg->render(getMemDC(), 10, 100 + 70 * nameSelectCount);
				}
				textBoxImg->render(getMemDC(), 0, 550);
				if (textLineNum == 1)
				{
					HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY¾èÀº»ù¹°M");
					HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

					char* name = INIDATA->loadDataString("data/playerData", "PLAYER", "NAME");
					DrawText(getMemDC(), name, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

					SelectObject(getMemDC(), oldFont);
					DeleteObject(myFont);
				}
				textOut();
			}
		}
	}
}

void characterCreationScene::selectArrowMove()
{
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (selectCount < 1)
		{
			selectCount++;
		}
		if (nameSelectCount < 3)
		{
			nameSelectCount++;
		}
	}
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (selectCount > 0)
		{
			selectCount--;
		}
		if (nameSelectCount > 0)
		{
			nameSelectCount--;
		}
	}
}

void characterCreationScene::loadPlayer()
{
	int loc = INIDATA->loadDataInteger("data/playerData", "PLAYER", "LOCATION");
	float centerX = INIDATA->loadDataFloat("data/playerData", "PLAYER", "centerX");
	float centerY = INIDATA->loadDataFloat("data/playerData", "PLAYER", "centerY");
	int moveLeftRight = INIDATA->loadDataInteger("data/playerData", "CAMERA", "moveLeftRight");
	int moveUpDown = INIDATA->loadDataInteger("data/playerData", "CAMERA", "moveUpDown");
	switch (loc)
	{
	case 0:
		PLAYER->setLocation(ROOM);
		break;
	case 1:
		PLAYER->setLocation(GOLDHOUSEFIRSTFLOOR);
		break;
	case 2:
		PLAYER->setLocation(STARTINGVILLIAGE);
		break;
	case 3:
		PLAYER->setLocation(POKELAB);
		break;
	case 4:
		PLAYER->setLocation(SHOP);
		break;
	case 5:
		PLAYER->setLocation(POKECENTER);
		break;
	case 6:
		PLAYER->setLocation(ROUTE30);
		break;
	}

	PLAYER->setCenterX(centerX);
	PLAYER->setCenterY(centerY);
	PLAYER->setMoveLeftRight(moveLeftRight);
	PLAYER->setMoveUpDown(moveUpDown);

	std::cout << PLAYER->getLocation() << "\t"
		<< PLAYER->getCenterX() << "\t"
		<< PLAYER->getCenterY() << "\t"
		<< PLAYER->getMoveLeftRight() << "\t"
		<< PLAYER->getMoveUpDown() << std::endl;

	SCENEMANAGER->loadScene("ÀÎ°ÔÀÓ");
}

void characterCreationScene::savePlayer()
{
	if (INPUT->GetKeyDown(VK_RETURN) && isSelectName)
	{
		switch (nameSelectCount)
		{
		case 0:
			INIDATA->addData("PLAYER", "NAME", "°ñµå");
			break;
		case 1:
			INIDATA->addData("PLAYER", "NAME", "¼öÈ£");
			break;
		case 2:
			INIDATA->addData("PLAYER", "NAME", "ÅÂ¾ç");
			break;
		case 3:
			INIDATA->addData("PLAYER", "NAME", "Ã¤¼öÇö");
			break;
		}
		INIDATA->saveINI("data/playerData");
		isResumeText = true;
		isSelectName = false;
	}
}

void characterCreationScene::DrOhAnimation()
{
	if (!isShowDrOh)
	{
		DrOhIndex = 0;
	}
	if (count % 20 == 0)
	{
		DrOhIndex++;
		if (DrOhIndex > 4 && isDrOhFadeIn)
		{
			DrOhIndex = 4;
		}
		if (DrOhIndex > 7 && isDrOhFadeOut)
		{
			DrOhIndex = 8;
		}
	}
}

void characterCreationScene::MarilAnimation()
{
	if (!isShowMaril)
	{
		MarilIndex = 0;
	}
	if (count % 20 == 0)
	{
		MarilIndex++;
		if (MarilIndex > 2 && isMarilFadeIn)
		{
			MarilIndex = 2;
		}
		if (MarilIndex > 4 && isMarilFadeOut)
		{
			MarilIndex = 5;
		}
	}
}

void characterCreationScene::goldAnimation()
{
	count++;
	if (count % 20 == 0)
	{
		goldIndex++;
		if (goldIndex > 4 && !isGoldTurnSD)
		{
			goldIndex = 5;
		}
	}
}

void characterCreationScene::setText(const char* fileName)
{
	HANDLE Text;
	char buf[512];
	char* token;
	DWORD nRead;
	Text = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (!openingLectureTextVector.empty())
	{
		openingLectureTextVector.clear();
	}

	ReadFile(Text, buf, 511, &nRead, NULL);

	a = 0;

	token = strtok(buf, "\n");

	while (token != NULL)
	{
		std::string* str = new std::string;
		str[0] = token;
		openingLectureTextVector.push_back(str);
		token = strtok(NULL, "\n");
		a++;
	}

	CloseHandle(Text);
}

void characterCreationScene::resumeText()
{
	if (isShowDrOh)
	{
		if (INPUT->GetKeyDown(VK_RETURN) || INPUT->GetKeyDown(VK_SPACE))
		{
			count = 0;
			if (textLineNum < a - 2)
			{
				textLineNum += 1;
				isResumeText = true;
			}
			if (textLineNum == 4)
			{
				isShowMaril = true;
				isMarilFadeIn = true;
			}
			if (textLineNum == a - 2)
			{
				isDrOhFadeIn = false;
				isMarilFadeIn = false;
				isDrOhFadeOut = true;
				isMarilFadeOut = true;
			}
		}
		if (DrOhIndex > 7 && MarilIndex > 4)
		{
			textLineNum = DrOhIndex = MarilIndex = 0;
			isDrOhFadeOut = false;
			isMarilFadeOut = false;
			isShowDrOh = false;
			isShowMaril = false;
			isShowGold = true;
			isStartNameSelection = true;
		}
	}
	else if (isShowGold)
	{
		if (INPUT->GetKeyDown(VK_RETURN) || INPUT->GetKeyDown(VK_SPACE))
		{
			if (textLineNum < a - 2)
			{
				textLineNum += 1;
				isResumeText = true;
			}
			if (textLineNum == a - 2)
			{
				isGoldTurnSD = true;
			}
		}
	}
}

void characterCreationScene::textOut()
{
	SetBkMode(getMemDC(), TRANSPARENT);

	HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY¾èÀº»ù¹°M");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	DrawText(getMemDC(), openingLectureTextVector[textLineNum]->c_str(), -1, &textDrawBox, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
	isResumeText = false;
}
