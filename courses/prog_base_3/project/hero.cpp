#include "hero.h"

Hero::Hero(std::string name, Picture * pic) {
	curHP = MAX_HP;
	usedHeroPower = false;
	this->name = name;
	this->pic = pic;
}

int Hero::getCurHP(void) {
	return curHP;
}

std::string Hero::getName(void) {
	return name;
}

void Hero::setCurHP(int newHP) {
	curHP = newHP;
}

bool Hero::hasUsedHeroPower(void) {
	return usedHeroPower;
}

void Hero::setHasUsedHeroPower(bool hasUsedHeroPower) {
	usedHeroPower = hasUsedHeroPower;
}