#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include "minionCard.h"
#define ALL_CARDS 16

// (it's actually STACK, it's not deck!)
class Deck {
	static const int MAX_CARD_AMOUNT = 30;
	int curCardAmount;
	MinionCard * cardList;
public:
	Deck();
	~Deck();
	int getCurCardAmount(void);
	void pushLast(MinionCard card);
	void pushRand(MinionCard card);
	MinionCard getByInd(int index);
	MinionCard popLast(void);
	void prepare(MinionCard arr[ALL_CARDS]);
	void repickPlayer(bool * chng, int isFirst);
	void repickComp(int isFirst);

private:
	bool isValidInd(int index);
	bool isEmpty(void);
	bool isFull(void);
};

#endif // DECK_H_INCLUDED