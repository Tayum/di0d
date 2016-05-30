#include <iostream>
#include <sstream>

#include "minionCard.h"

using namespace std;

MinionCard::MinionCard() {
	/*Picture pic = Picture("shadowOfNothing.png", 0, 0, 286, 395);
	this->pic = &pic;*/
	pic = nullptr;
	cardName = "NoName";
	attack = 0;
	curAttack = 0;
	health = 0;
	curHealth = 0;
	manacost = 0;
	taunt = false;
	attacked = true;
}
MinionCard::MinionCard(Picture * pic, std::string cardName, int attack, int health, int manacost, bool taunt) {
	this->pic = pic;
	this->cardName = cardName;
	this->attack = attack;
	curAttack = attack;
	this->health = health;
	curHealth = health;
	this->manacost = manacost;
	this->taunt = taunt;
	attacked = true;
}

int MinionCard::getManacost(void) {
	return manacost;
}

int MinionCard::getCurAttack(void) {
	return curAttack;
}

int MinionCard::getCurHealth(void) {
	return curHealth;
}

bool MinionCard::getTaunt(void) {
	return taunt;
}

bool MinionCard::hasAttacked(void) {
	return attacked;
}

void MinionCard::setCurHealth(int newHealth) {
	curHealth = newHealth;
}

void MinionCard::setCurAttack(int newAttack) {
	curAttack = newAttack;
}

void MinionCard::setHasAttacked(bool hasAttacked) {
	attacked = hasAttacked;
}

void MinionCard::attackCard(MinionCard  * cardDefender) {
	curHealth -= cardDefender->curAttack;
	cardDefender->curHealth -= curAttack;
	attacked = true;
}