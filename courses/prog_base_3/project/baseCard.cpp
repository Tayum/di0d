#include "baseCard.h"

int BaseCard::getCurCardAmount(void) {
	return curCardAmount;
}

bool BaseCard::isValidInd(int index) {
	return (index >= 0 && index < curCardAmount);
}

bool BaseCard::isEmpty(void) {
	return curCardAmount == 0;
}


// Function that uses virtual getter function
bool BaseCard::isFull(void) {
	return curCardAmount == getMaxCardAmount();
}


MinionCard BaseCard::getByInd(int index) {
	if (!isValidInd(index)) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[index];
		return card;
	}
}

// Battlefield / Hand classes
MinionCard BaseCard::delByInd(int index) {
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