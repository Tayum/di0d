#include "hand.h"

Hand::Hand() {
	lastCard = 0;
	curCardAmount = 0;
	cardList = new MinionCard[MAX_CARD_AMOUNT];
	mana = Mana();
}
Hand::~Hand() {
	delete[] cardList;
}

int Hand::getCurCardAmount(void) {
	return curCardAmount;
}

void Hand::addLast(MinionCard card) {
	if (!isFull()) {
		cardList[lastCard] = card;
		cardList[lastCard].pic->sprite.setScale(0.405, 0.425);
		lastCard++;
		curCardAmount++;
	}
}

MinionCard Hand::getByInd(int index) {
	if (!isValidInd(index)) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[index];
		return card;
	}
}

MinionCard Hand::delByInd(int index) {
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
		lastCard--;
		curCardAmount--;
		return card;
	}
}


bool Hand::isEmpty() {
	return curCardAmount == 0;
}

bool Hand::isValidInd(int index) {
	return (index >= 0 && index < curCardAmount);
}

// Private
bool Hand::isFull() {
	return curCardAmount == MAX_CARD_AMOUNT;
}