// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

// 자주사용하는 STL
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>;
using namespace std;


//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "input.h"
#include "random.h"
#include "imageManager.h"
#include "util.h"
#include "saveManager.h"
#include "sceneManager.h"
#include "iniData.h"
#include "decleration.h"
#include "Player.h"
#include "Pokemon.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace MY_UTIL;


//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define INPUT input::getSingleton() //세미콜론 찍으면 작동안함
#define RND random::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SAVEMANAGER saveManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define PLAYER playerData::getSingleton()
#define POKEMON Pokemon::getSingleton()


//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT(" 포켓몬스터 고-올드 "))
#define WINSTARTX	100
#define WINSTARTY	100
#define WINSIZEX		900
#define WINSIZEY		810
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;