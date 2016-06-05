#include "deck.h"

// (it's actually STACK, it's not deck!)
Deck::Deck() {
	curCardAmount = 0;
	cardList = new MinionCard[MAX_CARD_AMOUNT];
}
Deck::~Deck() {
	delete[] cardList;
}

int Deck::getCurCardAmount(void) {
	return curCardAmount;
}

void Deck::pushLast(MinionCard card) {
	if (!isFull()) {
		cardList[curCardAmount] = card;
		curCardAmount++;
	}
}

void Deck::pushRand(MinionCard card) {
	int index;
	if (!isFull()) {
		if (curCardAmount == 0) {
			cardList[curCardAmount] = card;
			curCardAmount++;
		}
		else {
			index = rand() % curCardAmount;
			if (index == curCardAmount) {
				cardList[curCardAmount] = card;
				curCardAmount++;
			}
			else {
				for (int i = curCardAmount; i > index; i--) {
					cardList[i] = cardList[i - 1];
				}
				cardList[index] = card;
				curCardAmount++;
			}
		}
	}
}

MinionCard Deck::getByInd(int index) {
	if (!isValidInd(index)) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[index];
		return card;
	}
}

MinionCard Deck::popLast(void) {
	if (isEmpty()) {
		MinionCard card = MinionCard();
		return card;
	}
	else {
		MinionCard card = cardList[curCardAmount - 1];
		curCardAmount--;
		return card;
	}
}

void Deck::prepare(MinionCard arr[ALL_CARDS]) {
	int counterArr[ALL_CARDS];
	for (int i = 0; i < ALL_CARDS; i++) {
		counterArr[i] = 0;
	}
	for (int i = 0; i < MAX_CARD_AMOUNT; i++) {
		int randNum = rand() % ALL_CARDS;
		if (counterArr[randNum] == 2) {
			i--;
			continue;
		}
		counterArr[randNum]++;

		MinionCard minBuff = arr[randNum];
		minBuff.pic = new Picture();
		memcpy(minBuff.pic, arr[randNum].pic, sizeof(Picture));
		pushRand(minBuff);

	}
}

void Deck::repickPlayer(bool * chng, int isFirst) {
	int indeces[4] = { -1,-1,-1,-1 };
	bool isValid;
	for (int i = 0; i < 4 - isFirst; i++) {
		isValid = true;
		if (chng[i]) {
			int index = rand() % 30;
			if (index >= 26 + isFirst) {
				i--;
				continue;
			}
			for (int j = 0; j < 4; j++) {
				if (indeces[j] == index) {
					i--;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				MinionCard temp = cardList[29 - i];
				cardList[29 - i] = cardList[index];
				cardList[index] = temp;
				indeces[i] = index;
			}
		}
	}
	delete[] chng;
}

void Deck::repickComp(int isFirst) {
	// What cards to repick
	bool chng[4] = { false,false,false,false };
	for (int i = 0; i < 4 - isFirst; i++) {
		if (cardList[29 - i].getManacost() >= 5) {
			chng[i] = true;
		}
	}
	// Actual repicking
	int indeces[4] = { -1,-1,-1,-1 };
	bool isValid;
	for (int i = 0; i < 4 - isFirst; i++) {
		isValid = true;
		if (chng[i]) {
			int index = rand() % 30;
			if (index >= 26 + isFirst) {
				i--;
				continue;
			}
			for (int j = 0; j < 4; j++) {
				if (indeces[j] == index) {
					i--;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				MinionCard temp = cardList[29 - i];
				cardList[29 - i] = cardList[index];
				cardList[index] = temp;
				indeces[i] = index;
			}
		}
	}
}

// Private
bool Deck::isValidInd(int index) {
	return (index >= 0 && index < curCardAmount);
}

bool Deck::isEmpty(void) {
	return curCardAmount == 0;
}

bool Deck::isFull(void) {
	return curCardAmount == MAX_CARD_AMOUNT;
}