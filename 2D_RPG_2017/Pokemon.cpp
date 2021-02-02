#include "stdafx.h"
#include "Pokemon.h"

HRESULT Pokemon::init()
{
	initPokemon();
	return S_OK;
}

void Pokemon::release()
{
	this->deleteAll();
}

void Pokemon::update()
{
}

void Pokemon::render()
{
}

BOOL Pokemon::deleteAll()
{
	/*pokemonIter iter = pokemon.begin();

	for (; iter != pokemon.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = pokemon.erase(iter);
		}
		else
		{
			iter++;
		}
	}*/

	pokemon.clear();

	return true;
}

void Pokemon::addSkill(std::string pokemonName, TYPE type, std::string name, int dmg, int maxPP, int prob)
{
	tagSkill temp;
	temp.type = type;
	temp.name = name;
	temp.damage = dmg;
	temp.maxPp = maxPP;
	temp.currentPP = maxPP;
	temp.prob = prob;
	this->findPokemon(pokemonName).skill.push_back(temp);
}

void Pokemon::addSkill(std::string pokemonName, int optionNum, TYPE type, std::string name, int dmg, int maxPP, int prob)
{
	if (this->findPokemon(pokemonName).skill.size() > 3)
	{
		tagSkill temp;
		temp.type = type;
		temp.name = name;
		temp.damage = dmg;
		temp.maxPp = maxPP;
		temp.prob = prob;

		this->findPokemon(pokemonName).skill.erase(this->findPokemon(pokemonName).skill.begin() + optionNum);
		this->findPokemon(pokemonName).skill.push_back(temp);
	}
	else
	{
		this->addSkill(pokemonName, type, name, dmg, maxPP, prob);
	}
}

void Pokemon::addPokemon(std::string key, const char* fileName, int number, std::string name, TYPE type, TYPE secondary)
{
	tagPokemon data;
	tagSkill skill;

	//memset(&data, 0, sizeof(data));
	data.img = IMAGEMANAGER->addImage(key, fileName, 810, 270);
	data.number = number;
	data.name = name;
	data.primarytype = type;
	data.secondaryType = secondary;

	pokemon.insert(make_pair(key, data));

}

void Pokemon::initPokemon()
{
	addPokemon("�̻��ؾ�", "images/Pokemon/001�̻��ؾ�.bmp", 1, "�̻��ؾ�", TYPE::Ǯ, TYPE::��);
	addPokemon("�̻���Ǯ", "images/Pokemon/002�̻���Ǯ.bmp", 2, "�̻���Ǯ", TYPE::Ǯ, TYPE::��);
	addPokemon("�̻��ز�", "images/Pokemon/003�̻��ز�.bmp", 3, "�̻��ز�", TYPE::Ǯ, TYPE::��);
	addPokemon("���̸�", "images/Pokemon/004���̸�.bmp", 4, "���̸�", TYPE::�Ҳ�, TYPE::����);
	addPokemon("���ڵ�", "images/Pokemon/005���ڵ�.bmp", 5, "���ڵ�", TYPE::�Ҳ�, TYPE::����);
	addPokemon("���ڸ�", "images/Pokemon/006���ڸ�.bmp", 6, "���ڸ�", TYPE::�Ҳ�, TYPE::����);
	addPokemon("���α�", "images/Pokemon/007���α�.bmp", 7, "���α�", TYPE::��, TYPE::����);
	addPokemon("��Ϻα�", "images/Pokemon/008��Ϻα�.bmp", 8, "��Ϻα�", TYPE::��, TYPE::����);
	addPokemon("�źϿ�", "images/Pokemon/009�źϿ�.bmp", 9, "�źϿ�", TYPE::��, TYPE::����);
	addPokemon("ĳ����", "images/Pokemon/010ĳ����.bmp", 10, "ĳ����", TYPE::����, TYPE::����);
	addPokemon("�ܵ���", "images/Pokemon/011�ܵ���.bmp", 11, "�ܵ���", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/012������.bmp", 12, "������", TYPE::����, TYPE::����);
	addPokemon("����", "images/Pokemon/016����.bmp", 16, "����", TYPE::�븻, TYPE::����);
	addPokemon("����", "images/Pokemon/017����.bmp", 17, "����", TYPE::�븻, TYPE::����);
	addPokemon("������", "images/Pokemon/018������.bmp", 18, "������", TYPE::�븻, TYPE::����);
	addPokemon("������", "images/Pokemon/021������.bmp", 21, "������", TYPE::�븻, TYPE::����);
	addPokemon("����帱��", "images/Pokemon/022����帱��.bmp", 22, "����帱��", TYPE::�븻, TYPE::����);
	addPokemon("��ī��", "images/Pokemon/025��ī��.bmp", 25, "��ī��", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/026������.bmp", 26, "������", TYPE::����, TYPE::����);
	addPokemon("�𷡵���", "images/Pokemon/027�𷡵���.bmp", 27, "�𷡵���", TYPE::��, TYPE::����);
	addPokemon("����", "images/Pokemon/028����.bmp", 28, "����", TYPE::��, TYPE::����);
	addPokemon("��Ű", "images/Pokemon/056��Ű.bmp", 56, "��Ű", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/057������.bmp", 57, "������", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/074������.bmp", 74, "������", TYPE::����, TYPE::��);
	addPokemon("������", "images/Pokemon/075������.bmp", 75, "������", TYPE::����, TYPE::��);
	addPokemon("������", "images/Pokemon/076������.bmp", 76, "������", TYPE::����, TYPE::��);
	addPokemon("�ߵ�", "images/Pokemon/079�ߵ�.bmp", 79, "�ߵ�", TYPE::��, TYPE::������);
	addPokemon("�ߵ���", "images/Pokemon/080�ߵ���.bmp", 80, "�ߵ���", TYPE::��, TYPE::������);
	addPokemon("��Ʈ", "images/Pokemon/092��Ʈ.bmp", 92, "��Ʈ", TYPE::��Ʈ, TYPE::��);
	addPokemon("��콺Ʈ", "images/Pokemon/093��콺Ʈ.bmp", 93, "��콺Ʈ", TYPE::��Ʈ, TYPE::��);
	addPokemon("����", "images/Pokemon/094����.bmp", 94, "����", TYPE::��Ʈ, TYPE::��);
	addPokemon("�ս���", "images/Pokemon/095�ս���.bmp", 95, "�ս���", TYPE::����, TYPE::��);
	addPokemon("����ũ", "images/Pokemon/123����ũ.bmp", 123, "����ũ", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/131������.bmp", 131, "������", TYPE::��, TYPE::����);
	addPokemon("�Ḹ��", "images/Pokemon/143�Ḹ��.bmp", 143, "�Ḹ��", TYPE::�븻, TYPE::����);
	addPokemon("�̴�", "images/Pokemon/147�̴�.bmp", 147, "�̴�", TYPE::�巡��, TYPE::����);
	addPokemon("�Ŵ�", "images/Pokemon/148�Ŵ�.bmp", 148, "�Ŵ�", TYPE::�巡��, TYPE::����);
	addPokemon("������", "images/Pokemon/149������.bmp", 149, "������", TYPE::�巡��, TYPE::����);
	addPokemon("����", "images/Pokemon/150����.bmp", 150, "����", TYPE::������, TYPE::����);
	addPokemon("��", "images/Pokemon/151��.bmp", 151, "��", TYPE::������, TYPE::����);
	addPokemon("ġ�ڸ�Ÿ", "images/Pokemon/152ġ�ڸ�Ÿ.bmp", 152, "ġ�ڸ�Ÿ", TYPE::Ǯ, TYPE::����);
	addPokemon("���̸���", "images/Pokemon/153���̸���.bmp", 153, "���̸���", TYPE::Ǯ, TYPE::����);
	addPokemon("�ް��Ͽ�", "images/Pokemon/154�ް��Ͽ�.bmp", 154, "�ް��Ͽ�", TYPE::Ǯ, TYPE::����);
	addPokemon("������", "images/Pokemon/155������.bmp", 155, "������", TYPE::�Ҳ�, TYPE::����);
	addPokemon("��������", "images/Pokemon/156��������.bmp", 156, "��������", TYPE::�Ҳ�, TYPE::����);
	addPokemon("���̹�", "images/Pokemon/157���̹�.bmp", 157, "���̹�", TYPE::�Ҳ�, TYPE::����);
	addPokemon("������", "images/Pokemon/158������.bmp", 158, "������", TYPE::��, TYPE::����);
	addPokemon("��������", "images/Pokemon/159��������.bmp", 159, "��������", TYPE::��, TYPE::����);
	addPokemon("��ũ�δ���", "images/Pokemon/160��ũ�δ���.bmp", 160, "��ũ�δ���", TYPE::��, TYPE::����);
	addPokemon("�ߵ�ŷ", "images/Pokemon/199�ߵ�ŷ.bmp", 199, "�ߵ�ŷ", TYPE::��, TYPE::������);
	addPokemon("��ö��", "images/Pokemon/208��ö��.bmp", 208, "��ö��", TYPE::��ö, TYPE::��);
	addPokemon("�ֻ�", "images/Pokemon/212�ֻ�.bmp", 212, "�ֻ�", TYPE::����, TYPE::��ö);
	addPokemon("���ũ�ν�", "images/Pokemon/214���ũ�ν�.bmp", 214, "���ũ�ν�", TYPE::����, TYPE::����);
	addPokemon("������", "images/Pokemon/227������.bmp", 227, "������", TYPE::��ö, TYPE::����);
	addPokemon("����", "images/Pokemon/228����.bmp", 228, "����", TYPE::��, TYPE::�Ҳ�);
	addPokemon("�ﰡ", "images/Pokemon/229�ﰡ.bmp", 229, "�ﰡ", TYPE::��, TYPE::�Ҳ�);
	addPokemon("�ֹ���", "images/Pokemon/246�ֹ���.bmp", 246, "�ֹ���", TYPE::����, TYPE::��);
	addPokemon("�����", "images/Pokemon/247�����.bmp", 247, "�����", TYPE::����, TYPE::��);
	addPokemon("�����", "images/Pokemon/248�����.bmp", 248, "�����", TYPE::����, TYPE::��);
	addPokemon("����", "images/Pokemon/249����.bmp", 249, "����", TYPE::������, TYPE::����);
	addPokemon("ĥ����", "images/Pokemon/250ĥ����.bmp", 250, "ĥ����", TYPE::�Ҳ�, TYPE::����);
}

tagPokemon Pokemon::findPokemon(std::string key)
{
	pokemonIter iter = pokemon.find(key);

	if (iter != pokemon.end())
	{
		return iter->second;
	}
}