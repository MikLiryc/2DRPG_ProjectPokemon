#include "stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init()
{
	initImages();

	enemy = POKEMON->findPokemon("����");
	enemy.level = 3;
	enemy.normalAtk = 15;
	enemy.normalDef = 15;
	enemy.specialAtk = 15;
	enemy.specialDef = 15;

	tagSkill temp;
	temp.type = TYPE::�Ҳ�;
	temp.skillType = SKILLTYPE::Ư��;
	temp.name = "�Ҳɼ���";
	temp.damage = 15;
	temp.maxPp = 25;
	temp.prob = 100;

	enemy.skill.push_back(temp);

	alpha = 255;
	enemyAlpha = 255;
	optionNum = 0;
	currentPokemonNum = 0;

	isPlayerTurn = isSelectAction = true;
	isEnemyTurn = isSelectPokemon = isSelectSkill = false;

	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update()
{
	if (isEnemyTurn)
	{

	}
	else if (isPlayerTurn)
	{
		if (isSelectAction && !isSelectPokemon && !isSelectSkill)
		{
			optionControl();
			selectAction();
		}
		else if (isSelectPokemon)
		{
			pokemonOptionControl();
			selectPokemon();
		}
		else if (isSelectSkill)
		{
			skillOptionControl();
		}
		if (INPUT->GetKeyDown(VK_F2))
		{
			currentPokemonNum++;
			if (currentPokemonNum > PLAYER->getPlayerPokemon().size() - 1)
			{
				currentPokemonNum = 0;
			}
		}
	}
	std::cout << _ptMouse.x << "\t" << _ptMouse.y << std::endl;
}

void battleScene::render()
{
	battleSceneBg->render(getMemDC(), 0, 0);

	PLAYER->getPlayerPokemon()[currentPokemonNum].img->alphaRender(getMemDC(), 70, 285, 540, 0, 270, 270, alpha);
	enemy.img->alphaRender(getMemDC(), 570, 0, 0, 0, 270, 270, enemyAlpha);

	//SetBkMode(getMemDC(), TRANSPARENT);
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	RECT textBox = RectMake(630, 400, 200, 30);
	char str[128];
	sprintf_s(str, PLAYER->getPlayerPokemon()[currentPokemonNum].name.c_str());
	DrawText(getMemDC(), str, -1, &textBox, DT_CENTER | DT_VCENTER);

	RECT textBox1 = RectMake(760, 430, 200, 30);
	char str1[256];
	sprintf_s(str1, "Lv : %d\0", PLAYER->getPlayerPokemon()[currentPokemonNum].level);
	DrawText(getMemDC(), str1, -1, &textBox1, DT_LEFT | DT_VCENTER);

	RECT textBox2 = RectMake(700, 460, 200, 30);
	char str2[128];
	sprintf_s(str2, "%d\0", PLAYER->getPlayerPokemon()[currentPokemonNum].hp);
	DrawText(getMemDC(), str2, -1, &textBox2, DT_LEFT| DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	if (isPlayerTurn)
	{
		if (isSelectAction && !isSelectSkill && !isSelectPokemon)
		{
			showOption();
			switch (optionNum)
			{
			case 0:
				selectArrow->render(getMemDC(), 30, 605);
				break;
			case 1:
				selectArrow->render(getMemDC(), 470, 605);
				break;
			case 2:
				selectArrow->render(getMemDC(), 30, 715);
				break;
			case 3:
				selectArrow->render(getMemDC(), 470, 715);
				break;
			}
		}
		else if (isSelectPokemon)
		{
			showPokemon();
		}
		else if (isSelectSkill)
		{
			showSkill();
			switch (optionNum)
			{
			case 0:
				selectArrow->render(getMemDC(), 30, 605);
				break;
			case 1:
				selectArrow->render(getMemDC(), 470, 605);
				break;
			case 2:
				selectArrow->render(getMemDC(), 30, 715);
				break;
			case 3:
				selectArrow->render(getMemDC(), 470, 715);
				break;
			}
		}
	}

	

}

void battleScene::initImages()
{
	battleSceneBg = IMAGEMANAGER->addImage("��Ʋ�����", "images/battleSceneBg.bmp", 900, 810);
	selectArrow = IMAGEMANAGER->addImage("SELECTARROW", "images/selectArrow.bmp", 50, 56);
	pokemonPageBg = IMAGEMANAGER->addImage("���ϸ���", "images/pokemonPage.bmp", 900, 810);
}

void battleScene::optionControl()
{
	if (INPUT->GetKeyDown(VK_LEFT))
	{
		if (optionNum == 1 || optionNum == 3)
		{
			optionNum -= 1;
		}
	}
	if (INPUT->GetKeyDown(VK_RIGHT))
	{
		if (optionNum == 0 || optionNum == 2)
		{
			optionNum += 1;
		}
	}
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (optionNum == 2)
		{
			optionNum = 0;
		}
		else if (optionNum == 3)
		{
			optionNum = 1;
		}
	}
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (optionNum == 0)
		{
			optionNum = 2;
		}
		else if (optionNum == 1)
		{
			optionNum = 3;
		}
	}
}

void battleScene::selectAction()
{
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		switch (optionNum)
		{
		case 0:
			optionNum = 0;
			isSelectSkill = true;
			attack(optionNum);
			break;
		case 1:
			optionNum = 0;
			isSelectPokemon = true;
			pokemon();
			break;
		case 2:
			optionNum = 0;
			bag();
			break;
		case 3:
			optionNum = 0;
			run();
			break;
		}
	}
}

void battleScene::showOption()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	RECT textDrawBox = RectMakeCenter(WINSIZEX / 2, 665, 830, 225);
	HFONT myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	char str[128];
	sprintf_s(str, "\n      ����                    ���ϸ� \n\n      ����                    ����ģ��");
	DrawText(getMemDC(), str, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void battleScene::attack(int num)
{
//	if (PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].currentPP > 0)
//	{
//		PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].currentPP -= 1;
//		
//		switch (PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].skillType)
//		{
//		case ����:
//			break;
//		case Ư��:
//			break;
//		default:
//			break;
//		}
//		if (PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].skillType == SKILLTYPE::����)
//		{
//			if (0 < PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].damage - enemy.normalDef)
//			{
//				enemy.hp -= PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].damage - enemy.normalDef;
//			}
//		}
//		if (PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].skillType == SKILLTYPE::Ư��)
//		{
//			if (0 < PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].damage - enemy.specialDef)
//			{
//				enemy.hp -= PLAYER->getPlayerPokemon()[currentPokemonNum].skill[num].damage - enemy.specialDef;
//			}
//		}
//	}
}

void battleScene::showSkill()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY��������M");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);


	for (int i = 0; i < PLAYER->getPlayerPokemon()[currentPokemonNum].skill.size(); i++)
	{
		RECT textDrawBox;
		switch (i)
		{
		case 0:
			textDrawBox = RectMake(80, 610, 450, 100);
			break;
		case 1:
			textDrawBox = RectMake(530, 610, 450, 100);
			break;
		case 2:
			textDrawBox = RectMake(80, 715, 450, 100);
			break;
		case 3:
			textDrawBox = RectMake(530, 715, 450, 100);
			break;
		}
		char str[128];
		sprintf_s(str, "%s \n����: %d   ����: %d   PP: %d / %d",
			PLAYER->getPlayerPokemon()[currentPokemonNum].skill[i].name.c_str(),
			PLAYER->getPlayerPokemon()[currentPokemonNum].skill[i].damage,
			PLAYER->getPlayerPokemon()[currentPokemonNum].skill[i].prob,
			PLAYER->getPlayerPokemon()[currentPokemonNum].skill[i].currentPP,
			PLAYER->getPlayerPokemon()[currentPokemonNum].skill[i].maxPp);
		DrawText(getMemDC(), str, -1, &textDrawBox, DT_LEFT | DT_VCENTER);

	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void battleScene::skillOptionControl()
{
	if (INPUT->GetKeyDown(VK_LEFT))
	{
		if (optionNum == 1 || optionNum == 3)
		{
			optionNum -= 1;
		}
	}
	if (INPUT->GetKeyDown(VK_RIGHT))
	{
		if (optionNum == 0 || optionNum == 2)
		{
			optionNum += 1;
		}
	}
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (optionNum == 2)
		{
			optionNum = 0;
		}
		else if (optionNum == 3)
		{
			optionNum = 1;
		}
	}
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (optionNum == 0)
		{
			optionNum = 2;
		}
		else if (optionNum == 1)
		{
			optionNum = 3;
		}
	}
	if (INPUT->GetKeyDown(VK_BACK))
	{
		optionNum = 0;
		isSelectSkill = false;
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		attack(optionNum);
	}
}

void battleScene::enemyAttack()
{
}

void battleScene::pokemon()
{
}

void battleScene::showPokemon()
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

void battleScene::pokemonOptionControl()
{
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (optionNum > 0)
		{
			optionNum--;;
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
		currentPokemonNum = optionNum;
		optionNum = 0;
		isSelectPokemon = false;
	}
}

void battleScene::bag()
{
}

void battleScene::run()
{
	int num = RND->range(100);
	if (num < 50)
	{
		PLAYER->setIsEncounter(false);
		SCENEMANAGER->loadScene("�ΰ���");
	}
}

void battleScene::selectPokemon()
{
}
