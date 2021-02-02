#pragma once
#include "singletonBase.h"

class Pokemon :
	public singletonBase<Pokemon>
{
private:
	typedef std::unordered_map<std::string, tagPokemon> pokemonList;
	typedef std::unordered_map<std::string, tagPokemon>::iterator pokemonIter;

	pokemonList pokemon;

	tagPokemon data;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	BOOL deleteAll();

	void addSkill(std::string pokemonName, TYPE type, std::string name, int dmg, int maxPP, int prob);
	void addSkill(std::string pokemonName, int optionNum, TYPE type, std::string name, int dmg, int maxPP, int prob);
	void addPokemon(std::string key, const char* fileName, int number, std::string name, TYPE type, TYPE secondary);
	void initPokemon();
	tagPokemon findPokemon(std::string key);

};

