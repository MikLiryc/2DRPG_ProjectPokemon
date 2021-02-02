#include "stdafx.h"
#include "saveManager.h"

HRESULT saveManager::init()
{
	return S_OK;
}

void saveManager::release()
{
}

void saveManager::loadPlayerData()
{
	HANDLE saveData;
	saveData = CreateFile("saveData.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	char buf[512];
	char* token;
	DWORD nread;

	ReadFile(saveData, buf, 511, &nread, NULL);

	token = strtok(buf, " ");
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			playerData.hp = atoi(token);
			token = strtok(NULL, " ");
			break;
		case 1:
			playerData.x = atof(token);
			token = strtok(NULL, " ");
			break;
		case 2:
			playerData.y = atof(token);
			break;
		}
	}

	CloseHandle(saveData);
}

void saveManager::savePlayerData(int hp, float x, float y)
{
	HANDLE saveData;
	char buf[512];
	DWORD nread, nwrite;
	saveData = CreateFile("saveData.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

	sprintf_s(buf, "%d %f %f", hp, x, y);

	WriteFile(saveData, buf, sizeof(buf), &nwrite, NULL);

	CloseHandle(saveData);
}
