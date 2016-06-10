#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include "BaseCard.h"
#define ALL_CARDS 16


class Deck : public BaseCard {
	static const int MAX_CARD_AMOUNT = 30;
	// Getter function for static variable
	int getMaxCardAmount(void) const;
public:
	Deck();
	~Deck();
	void pushLast(MinionCard card);
	void pushRand(MinionCard card);
	MinionCard popLast(void);
	void prepare(MinionCard arr[ALL_CARDS]);
	void repickPlayer(bool * chng, int isFirst);
	void repickComp(int isFirst);
};

#endif // DECK_H_INCLUDED