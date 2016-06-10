#include "hand.h"

Hand::Hand() {
	curCardAmount = 0;
	cardList = new MinionCard[MAX_CARD_AMOUNT];
	mana = Mana();
}
Hand::~Hand() {
	delete[] cardList;
}

// Getter function for static variable
int Hand::getMaxCardAmount(void) const {
	return MAX_CARD_AMOUNT;
}

void Hand::addLast(MinionCard card) {
	if (!isFull()) {
		cardList[curCardAmount] = card;
		cardList[curCardAmount].pic->sprite.setScale(0.405, 0.425);
		curCardAmount++;
	}
}