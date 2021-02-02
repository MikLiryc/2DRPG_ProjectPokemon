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
	addPokemon("이상해씨", "images/Pokemon/001이상해씨.bmp", 1, "이상해씨", TYPE::풀, TYPE::독);
	addPokemon("이상해풀", "images/Pokemon/002이상해풀.bmp", 2, "이상해풀", TYPE::풀, TYPE::독);
	addPokemon("이상해꽃", "images/Pokemon/003이상해꽃.bmp", 3, "이상해꽃", TYPE::풀, TYPE::독);
	addPokemon("파이리", "images/Pokemon/004파이리.bmp", 4, "파이리", TYPE::불꽃, TYPE::없음);
	addPokemon("리자드", "images/Pokemon/005리자드.bmp", 5, "리자드", TYPE::불꽃, TYPE::없음);
	addPokemon("리자몽", "images/Pokemon/006리자몽.bmp", 6, "리자몽", TYPE::불꽃, TYPE::비행);
	addPokemon("꼬부기", "images/Pokemon/007꼬부기.bmp", 7, "꼬부기", TYPE::물, TYPE::없음);
	addPokemon("어니부기", "images/Pokemon/008어니부기.bmp", 8, "어니부기", TYPE::물, TYPE::없음);
	addPokemon("거북왕", "images/Pokemon/009거북왕.bmp", 9, "거북왕", TYPE::물, TYPE::없음);
	addPokemon("캐터피", "images/Pokemon/010캐터피.bmp", 10, "캐터피", TYPE::벌레, TYPE::없음);
	addPokemon("단데기", "images/Pokemon/011단데기.bmp", 11, "단데기", TYPE::벌레, TYPE::없음);
	addPokemon("버터플", "images/Pokemon/012버터플.bmp", 12, "버터플", TYPE::벌레, TYPE::비행);
	addPokemon("구구", "images/Pokemon/016구구.bmp", 16, "구구", TYPE::노말, TYPE::비행);
	addPokemon("피죤", "images/Pokemon/017피죤.bmp", 17, "피죤", TYPE::노말, TYPE::비행);
	addPokemon("피죤투", "images/Pokemon/018피죤투.bmp", 18, "피죤투", TYPE::노말, TYPE::비행);
	addPokemon("깨비참", "images/Pokemon/021깨비참.bmp", 21, "깨비참", TYPE::노말, TYPE::비행);
	addPokemon("깨비드릴조", "images/Pokemon/022깨비드릴조.bmp", 22, "깨비드릴조", TYPE::노말, TYPE::비행);
	addPokemon("피카츄", "images/Pokemon/025피카츄.bmp", 25, "피카츄", TYPE::전기, TYPE::없음);
	addPokemon("라이츄", "images/Pokemon/026라이츄.bmp", 26, "라이츄", TYPE::전기, TYPE::없음);
	addPokemon("모래두지", "images/Pokemon/027모래두지.bmp", 27, "모래두지", TYPE::땅, TYPE::없음);
	addPokemon("고지", "images/Pokemon/028고지.bmp", 28, "고지", TYPE::땅, TYPE::없음);
	addPokemon("망키", "images/Pokemon/056망키.bmp", 56, "망키", TYPE::격투, TYPE::없음);
	addPokemon("성원숭", "images/Pokemon/057성원숭.bmp", 57, "성원숭", TYPE::격투, TYPE::없음);
	addPokemon("꼬마돌", "images/Pokemon/074꼬마돌.bmp", 74, "꼬마돌", TYPE::바위, TYPE::땅);
	addPokemon("데구리", "images/Pokemon/075데구리.bmp", 75, "데구리", TYPE::바위, TYPE::땅);
	addPokemon("딱구리", "images/Pokemon/076딱구리.bmp", 76, "딱구리", TYPE::바위, TYPE::땅);
	addPokemon("야돈", "images/Pokemon/079야돈.bmp", 79, "야돈", TYPE::물, TYPE::에스퍼);
	addPokemon("야도란", "images/Pokemon/080야도란.bmp", 80, "야도란", TYPE::물, TYPE::에스퍼);
	addPokemon("고스트", "images/Pokemon/092고스트.bmp", 92, "고스트", TYPE::고스트, TYPE::독);
	addPokemon("고우스트", "images/Pokemon/093고우스트.bmp", 93, "고우스트", TYPE::고스트, TYPE::독);
	addPokemon("팬텀", "images/Pokemon/094팬텀.bmp", 94, "팬텀", TYPE::고스트, TYPE::독);
	addPokemon("롱스톤", "images/Pokemon/095롱스톤.bmp", 95, "롱스톤", TYPE::바위, TYPE::땅);
	addPokemon("스라크", "images/Pokemon/123스라크.bmp", 123, "스라크", TYPE::벌레, TYPE::비행);
	addPokemon("라프라스", "images/Pokemon/131라프라스.bmp", 131, "라프라스", TYPE::물, TYPE::얼음);
	addPokemon("잠만보", "images/Pokemon/143잠만보.bmp", 143, "잠만보", TYPE::노말, TYPE::없음);
	addPokemon("미뇽", "images/Pokemon/147미뇽.bmp", 147, "미뇽", TYPE::드래곤, TYPE::없음);
	addPokemon("신뇽", "images/Pokemon/148신뇽.bmp", 148, "신뇽", TYPE::드래곤, TYPE::없음);
	addPokemon("망나뇽", "images/Pokemon/149망나뇽.bmp", 149, "망나뇽", TYPE::드래곤, TYPE::비행);
	addPokemon("뮤츠", "images/Pokemon/150뮤츠.bmp", 150, "뮤츠", TYPE::에스퍼, TYPE::없음);
	addPokemon("뮤", "images/Pokemon/151뮤.bmp", 151, "뮤", TYPE::에스퍼, TYPE::없음);
	addPokemon("치코리타", "images/Pokemon/152치코리타.bmp", 152, "치코리타", TYPE::풀, TYPE::없음);
	addPokemon("베이리프", "images/Pokemon/153베이리프.bmp", 153, "베이리프", TYPE::풀, TYPE::없음);
	addPokemon("메가니움", "images/Pokemon/154메가니움.bmp", 154, "메가니움", TYPE::풀, TYPE::없음);
	addPokemon("브케인", "images/Pokemon/155브케인.bmp", 155, "브케인", TYPE::불꽃, TYPE::없음);
	addPokemon("마그케인", "images/Pokemon/156마그케인.bmp", 156, "마그케인", TYPE::불꽃, TYPE::없음);
	addPokemon("블레이범", "images/Pokemon/157블레이범.bmp", 157, "블레이범", TYPE::불꽃, TYPE::없음);
	addPokemon("리아코", "images/Pokemon/158리아코.bmp", 158, "리아코", TYPE::물, TYPE::없음);
	addPokemon("엘리게이", "images/Pokemon/159엘리게이.bmp", 159, "엘리게이", TYPE::물, TYPE::없음);
	addPokemon("장크로다일", "images/Pokemon/160장크로다일.bmp", 160, "장크로다일", TYPE::물, TYPE::없음);
	addPokemon("야도킹", "images/Pokemon/199야도킹.bmp", 199, "야도킹", TYPE::물, TYPE::에스퍼);
	addPokemon("강철톤", "images/Pokemon/208강철톤.bmp", 208, "강철톤", TYPE::강철, TYPE::땅);
	addPokemon("핫삼", "images/Pokemon/212핫삼.bmp", 212, "핫삼", TYPE::벌레, TYPE::강철);
	addPokemon("헤라크로스", "images/Pokemon/214헤라크로스.bmp", 214, "헤라크로스", TYPE::벌레, TYPE::격투);
	addPokemon("무장조", "images/Pokemon/227무장조.bmp", 227, "무장조", TYPE::강철, TYPE::비행);
	addPokemon("델빌", "images/Pokemon/228델빌.bmp", 228, "델빌", TYPE::악, TYPE::불꽃);
	addPokemon("헬가", "images/Pokemon/229헬가.bmp", 229, "헬가", TYPE::악, TYPE::불꽃);
	addPokemon("애버라스", "images/Pokemon/246애버라스.bmp", 246, "애버라스", TYPE::바위, TYPE::땅);
	addPokemon("데기라스", "images/Pokemon/247데기라스.bmp", 247, "데기라스", TYPE::바위, TYPE::땅);
	addPokemon("마기라스", "images/Pokemon/248마기라스.bmp", 248, "마기라스", TYPE::바위, TYPE::악);
	addPokemon("루기아", "images/Pokemon/249루기아.bmp", 249, "루기아", TYPE::에스퍼, TYPE::비행);
	addPokemon("칠색조", "images/Pokemon/250칠색조.bmp", 250, "칠색조", TYPE::불꽃, TYPE::비행);
}

tagPokemon Pokemon::findPokemon(std::string key)
{
	pokemonIter iter = pokemon.find(key);

	if (iter != pokemon.end())
	{
		return iter->second;
	}
}