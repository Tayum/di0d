#include "battlefield.h"

Battlefield::Battlefield() {
	curCardAmount = 0;
	cardList = new MinionCard[MAX_CARD_AMOUNT];
}
Battlefield::~Battlefield() {
	delete[] cardList;
}

// Getter function for static variable
int Battlefield::getMaxCardAmount(void) const {
	return MAX_CARD_AMOUNT;
}

void Battlefield::addLast(MinionCard card) {
	if (!isFull()) {
		cardList[curCardAmount] = card;
		cardList[curCardAmount].pic->sprite.setScale(0.671, 0.567);
		curCardAmount++;
	}
}

void Battlefield::checkDead(void) {
	for (int i = 0; i < curCardAmount; i++) {
		if (cardList[i].getCurHealth() <= 0) {
			delByInd(i);
			break;
		}
	}
}

bool Battlefield::isThereTaunts(void) {
	for (int i = 0; i < curCardAmount; i++) {
		if (cardList[i].getTaunt()) {
			return true;
		}
	}
	return false;
}