#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <iostream>
#include <sstream>

#include "picture.h"

class Hero {
	static const int MAX_HP = 30;
	int curHP;
	std::string name;
	bool usedHeroPower;
public:
	Picture * pic;

	Hero(std::string name, Picture * pic);
	int getCurHP(void);
	std::string getName(void);
	void setCurHP(int newHP);
	bool hasUsedHeroPower(void);
	void setHasUsedHeroPower(bool hasUsedHeroPower);

};

#endif // HERO_H_INCLUDED