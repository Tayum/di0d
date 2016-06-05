#ifndef BATTLEFIELD_H_INCLUDED
#define BATTLEFIELD_H_INCLUDED

#include "minionCard.h"

class Battlefield {
	static const int MAX_CARD_AMOUNT = 7;
	int curCardAmount;
public:
	MinionCard * cardList;

	Battlefield();
	~Battlefield();

	int getCurCardAmount(void);
	void addLast(MinionCard card);
	MinionCard getByInd(int index);
	MinionCard delByInd(int index);
	void checkDead(void);
	bool isValidInd(int index);
	bool isThereTaunts();
	bool isFull();
private:
	bool isEmpty();
};

#endif // BATTLEFIELD_H_INCLUDED