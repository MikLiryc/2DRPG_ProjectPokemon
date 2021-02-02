#pragma once
#include "singletonBase.h"

struct tagIniData
{
	char* section;  //[Player]
	char* key;      //HP=100
	char* value;
};

class iniData : public singletonBase<iniData>
{
private:
	std::vector<tagIniData> _vIniData;



public:
	HRESULT init();
	void release();

	//������ �߰��ϱ�
	void addData(const char* section, const char* key, const char* value);

	//������ ���̺�
	void saveINI(const char* fileName);

	//���ڷ� ���� �ε��ϱ� (�����̸�, �ش� ����, Ű)
	char* loadDataString(const char* fileName, const char* section, const char* key);
	//������ ���� �ε��ϱ� (�����̸�, ����, Ű)
	int loadDataInteger(const char* fileName, const char* section, const char* key);
	//�Ǽ��� �� �ε�
	float loadDataFloat(const char* fileName, const char* section, const char* key);


};

