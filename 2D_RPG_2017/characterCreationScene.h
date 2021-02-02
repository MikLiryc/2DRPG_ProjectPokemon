#pragma once
#include "gameNode.h"

class characterCreationScene :
	public gameNode
{
private:
	image* backgroundImg;
	image* startTextBoxImg;
	image* textBoxImg;
	image* selectArrowImg;
	image* downArrowImg;
	image* DrOhImg;
	image* marilImg;
	image* goldImg;
	image* nameSelectBoxImg;

	RECT textDrawBox;

	std::vector<std::string*> openingLectureTextVector;
	char* textOutText;

	int a;
	int textLineNum;
	int selectCount, nameSelectCount, count;
	int DrOhIndex, MarilIndex, goldIndex;
	bool isStart, isShowDrOh, isDrOhFadeIn, isDrOhFadeOut;
	bool isShowMaril, isMarilFadeIn, isMarilFadeOut;
	bool isGoldTurnSD, isSelectName;
	bool isResumeText;
	bool isShowGold, isStartNameSelection;

	char* text;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void selectArrowMove();
	void loadPlayer();
	void savePlayer();

	void DrOhAnimation();
	void MarilAnimation();
	void goldAnimation();

	void setText(const char* fileName);
	void resumeText();
	void textOut();
};

