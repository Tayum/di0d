#include "mana.h"

// Implemented in hand class
Mana::Mana() {
	curMana = 0;
	curMaxMana = 0;
}

int Mana::getCurMana(void) {
	return curMana;
}

int Mana::getCurMaxMana(void) {
	return curMaxMana;
}

bool Mana::isEnough(MinionCard card) {
	return curMana >= card.getManacost();
}
bool Mana::isEnough(int reqMana) {
	return curMana >= reqMana;
}

void Mana::useCard(MinionCard card) {
	if (isEnough(card)) {
		curMana -= card.getManacost();
	}
}
void Mana::useHeroPower(void) {
	if (isEnough(2)) {
		curMana -= 2;
	}
}

void Mana::onTurnStart(void) {
	manaGrow();
	manaReplenish();
}

// Private
void Mana::manaGrow(void) {
	if (curMaxMana != MAX_MANA) {
		curMaxMana++;
	}
}

void Mana::manaReplenish(void) {
	curMana = curMaxMana;
}