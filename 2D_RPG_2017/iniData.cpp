#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release()
{
}

//������ �߰��ϱ�
void iniData::addData(const char* section, const char* key, const char* value)
{
	//ini ������ ����ü �ʱ�ȭ
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	data.value = (char*)value;
	//���Ϳ� ���
	_vIniData.push_back(data);
}

//������ ���̺�
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

//���ڷ� ���� �ε��ϱ� (�����̸�, �ش� ����, Ű)
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
//������ ���� �ε��ϱ� (�����̸�, �ش� ����, Ű)
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
//�Ǽ��� ���� �ε��ϱ� (�����̸�, �ش� ����, Ű)
float iniData::loadDataFloat(const char* fileName, const char* section, const char* key)
{
	return (atof)(loadDataString(fileName, section, key));
	//���ڿ��� �ε� �ؼ� �Ǽ��� ����ȯ
}
