#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED

#include "minionCard.h"
#include "mana.h"

class Hand {
	static const int MAX_CARD_AMOUNT = 10;
	int curCardAmount;
public:
	MinionCard * cardList;
	Mana mana;

	Hand();
	~Hand();
	int getCurCardAmount(void);
	void addLast(MinionCard card);
	MinionCard getByInd(int index);
	MinionCard delByInd(int index);
	bool isEmpty();
	bool isValidInd(int index);

private:
	bool isFull();

};

#endif // HAND_H_INCLUDED