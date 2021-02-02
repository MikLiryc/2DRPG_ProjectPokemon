#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release()
{
}

//데이터 추가하기
void iniData::addData(const char* section, const char* key, const char* value)
{
	//ini 데이터 구조체 초기화
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	data.value = (char*)value;
	//벡터에 담기
	_vIniData.push_back(data);
}

//데이터 세이브
void iniData::saveINI(const char* fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}

//문자로 값을 로드하기 (파일이름, 해당 섹션, 키)
char* iniData::loadDataString(const char* fileName, const char* section, const char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	char data[64] = { 0 };

	GetPrivateProfileString(section, key, " ", data, 64, dir);

	return data;
}
//정수로 값을 로드하기 (파일이름, 해당 섹션, 키)
int iniData::loadDataInteger(const char* fileName, const char* section, const char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}
//실수로 값을 로드하기 (파일이름, 해당 섹션, 키)
float iniData::loadDataFloat(const char* fileName, const char* section, const char* key)
{
	return (atof)(loadDataString(fileName, section, key));
	//문자열을 로드 해서 실수로 형변환
}
