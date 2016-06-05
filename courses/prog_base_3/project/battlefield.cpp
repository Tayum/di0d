#include "battlefield.h"

Battlefield::Battlefield() {
	curCardAmount = 0;
	cardList = new MinionCard[MAX_CARD_AMOUNT];
}
Battlefield::~Battlefield() {
	delete[] cardList;
}

int Battlefield::getCurCardAmount(void) {
	return curCardAmount;
}

void Battlefield::addLast(MinionCard card) {
	if (!isFull()) {
		cardList[curCardAmount] = card;
		cardList[curCardAmount].pic->sprite.setScale(0.671, 0.405);
		curCardAmount++;
	}
}

MinionCard Battlefield::getByInd(int index) {
	if (!isValidInd(index)) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[index];
		return card;
	}
}

MinionCard Battlefield::delByInd(int index) {
	int i;
	if (!isValidInd(index)) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[index];
		for (i = index; i < curCardAmount - 1; i++) {
			cardList[i] = cardList[i + 1];
		}
		curCardAmount--;
		return card;
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

bool Battlefield::isValidInd(int index) {
	return (index >= 0 && index < curCardAmount);
}

bool Battlefield::isThereTaunts() {
	for (int i = 0; i < curCardAmount; i++) {
		if (cardList[i].getTaunt()) {
			return true;
		}
	}
	return false;
}

bool Battlefield::isFull() {
	return curCardAmount == MAX_CARD_AMOUNT;
}
// Private
bool Battlefield::isEmpty() {
	return curCardAmount == 0;
}