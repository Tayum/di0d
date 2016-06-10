#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED

#include "baseCard.h"
#include "mana.h"

class Hand : public BaseCard {
	static const int MAX_CARD_AMOUNT = 10;
	// Getter function for static variable
	int getMaxCardAmount(void) const;
public:
	Mana mana;

	Hand();
	~Hand();
	void addLast(MinionCard card);
};

#endif // HAND_H_INCLUDED