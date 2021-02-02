#include "stdafx.h"
#include "introScene.h"

HRESULT introScene::init()
{
	introBgImg = IMAGEMANAGER->addImage("INTROBG", "images/introBg.bmp", 900, 810);
	introCloudImg = IMAGEMANAGER->addImage("INTROCLOUD", "images/introCloud.bmp", 900, 810);
	introHoOhImg = IMAGEMANAGER->addFrameImage("INTROHOOH", "images/introHoOh.bmp", 1500, 230, 5, 1);
	introParticleImg = IMAGEMANAGER->addFrameImage("INTROPARTICLE", "images/introParticle.bmp", 100, 75, 2, 1);

	introDrawBox = RectMake(0, 0, WINSIZEX, WINSIZEY);
	startDrawBox = RectMakeCenter(WINSIZEX / 2, 680, 450, 50);

	for (int i = 0; i < 10; i++)
	{
		introParticle[i].img = introParticleImg;
		introParticle[i].angle = 2 * M_PI - 2 * (2 * M_PI / 36);
		introParticle[i].speed = 8.0f;
		introParticle[i].centerX = -50;
		introParticle[i].centerY = -80;
		introParticle[i].isShow = false;
	}

	index = 0;
	particleIndex = 0;
	count = 0;
	loopX = 0.0f;
	hoOhCenterX = WINSIZEX / 2;
	hoOhCenterY = 500;
	isSceneEnd = false;
	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	introAnimation();
	particleMove();
	particleOutOfScreen();

	loopX -= 0.3f;

	if (INPUT->GetKeyDown(VK_SPACE))
	{
		SCENEMANAGER->loadScene("캐릭터생성");
	}
	if (INPUT->GetKeyDown(VK_LCONTROL))
	{
		SCENEMANAGER->loadScene("인게임");
	}
}

void introScene::render()
{
	introBgImg->render(getMemDC());
	introCloudImg->loopRender(getMemDC(), &introDrawBox, loopX, 0);
	introHoOhImg->frameRender(getMemDC(), hoOhCenterX - 150, hoOhCenterY - 115, index, 0);
	for (int i = 0; i < 10; i++)
	{
		if (!introParticle[i].isShow) { continue; }
		introParticle[i].img->frameRender(getMemDC(), introParticle[i].centerX - 25, introParticle[i].centerY - 33, particleIndex, 0);
	}

	SetBkMode(getMemDC(), TRANSPARENT);

	HFONT myFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "HY얕은샘물M");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	DrawText(getMemDC(), "PRESS SPACE TO START", -1, &startDrawBox, DT_CENTER | DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void introScene::introAnimation()
{
	count += 1;
	if (count % 10 == 0)
	{
		index++;
		setParticlePos();
		if (index > 4)
		{
			index = 0;
			setParticlePos();
		}
		count = 0;
	}
	if (count % 5 == 0)
	{
		particleIndex++;
		if (particleIndex > 1)
		{
			particleIndex = 0;
		}
	}
}

void introScene::setParticlePos()
{
	for (int i = 0; i < 10; i++)
	{
		if (introParticle[i].isShow) { continue; }
		switch (index)
		{
		case 0:
			introParticle[i].centerX = 420;
			introParticle[i].centerY = 430;
			introParticle[i].isShow = true;
			break;
		case 1:
			introParticle[i].centerX = 400;
			introParticle[i].centerY = 500;
			introParticle[i].isShow = true;
			break;
		case 2:
			introParticle[i].centerX = 450;
			introParticle[i].centerY = 580;
			introParticle[i].isShow = true;
			introParticle[i + 1].centerX = 500;
			introParticle[i + 1].centerY = 475;
			introParticle[i + 1].isShow = true;
			break;
		case 3:
			//introParticle[i].centerX = 440;
			//introParticle[i].centerY = 475;
			//introParticle[i].isShow = true;
			break;
		case 4:
			introParticle[i].centerX = 470;
			introParticle[i].centerY = 400;
			introParticle[i].isShow = true;
			break;
		}
		break;
	}
}

void introScene::particleOutOfScreen()
{
	for (int i = 0; i < 10; i++)
	{
		if (introParticle[i].centerX > WINSIZEX + 25 || introParticle[i].centerY > WINSIZEY + 33)
		{
			introParticle[i].isShow = false;
		}
	}
}

void introScene::particleMove()
{
	for (int i = 0; i < 10; i++)
	{
		if (!introParticle[i].isShow) { continue; }
		introParticle[i].centerX += cosf(introParticle[i].angle) * introParticle[i].speed;
		introParticle[i].centerY += -sinf(introParticle[i].angle) * introParticle[i].speed;
	}
}
