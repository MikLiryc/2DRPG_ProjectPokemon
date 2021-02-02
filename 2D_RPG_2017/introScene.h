#pragma once
#include "gameNode.h"

struct tagParticle
{
	image* img;
	float centerX, centerY, angle;
	float speed;
	bool isShow;
};

class introScene :
	public gameNode
{
private:
	int count, index, particleIndex;
	float loopX;
	int hoOhCenterX, hoOhCenterY;
	bool isSceneEnd;

	image* introBgImg;
	image* introCloudImg;
	image* introHoOhImg;
	image* introParticleImg;
	RECT introDrawBox;
	RECT startDrawBox;
	tagParticle introParticle[10];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void introAnimation();
	void setParticlePos();
	void particleOutOfScreen();
	void particleMove();
};
