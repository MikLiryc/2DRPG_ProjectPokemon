#pragma once

enum LOCATION
{
	ROOM,
	GOLDHOUSEFIRSTFLOOR,
	STARTINGVILLIAGE,
	POKELAB,
	SHOP,
	POKECENTER,
	ROUTE30
};

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class STATE
{
	IDLE,
	RUN
};

enum class TYPE
{
	����,
	�븻,
	�Ҳ�,
	��,
	����,
	Ǯ,
	����,
	����,
	��,
	��,
	����,
	������,
	����,
	����,
	��Ʈ,
	�巡��,
	��,
	��ö
};

enum SKILLTYPE
{
	����,
	Ư��
};

struct tagSkill
{
	TYPE type;
	SKILLTYPE skillType;
	std::string name;
	int damage;
	int maxPp;
	int currentPP;
	int prob;
};

struct tagPokemon
{
	image* img;
	std::string name;
	int number;
	int hp;
	int level;
	int exp;
	int normalAtk, specialAtk;
	int normalDef, specialDef;
	int speed;
	TYPE primarytype;
	TYPE secondaryType;
	std::vector<tagSkill> skill;
};

#define SIZE 6
struct cirQueue
{
	tagPokemon* arr[SIZE];
	int front, rear;

	cirQueue()
	{
		front = SIZE - 1;
		rear = SIZE - 1;
	}

	bool isEmpty()
	{
		return rear == front;
	}

	bool isFull()
	{
		return ((rear + 1) % SIZE) == front;
	}

	void enqueue(tagPokemon* data)
	{
		if (isFull())
		{
			cout << "Q is full" << endl;
			return;
		}
		rear = (rear + 1) % SIZE;
		arr[rear] = data;
	}

	tagPokemon* dequeue()
	{
		if (isEmpty())
		{
			cout << "Q is empty" << endl;
			return 0;
		}
		return arr[front = (front + 1) % SIZE];
	}
};
