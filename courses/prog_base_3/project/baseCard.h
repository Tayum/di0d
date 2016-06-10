#ifndef BASECARD_H_INCLUDED
#define BASECARD_H_INCLUDED

#include "minionCard.h"

// An abstract class, which holds !(shared)! (same logic) variables and functions.
// These variables and functions are used in Battlefield, Deck and Hand classes.
class BaseCard {
	// All classes
protected:
	int curCardAmount;
public:
	MinionCard * cardList;

	int getCurCardAmount(void);
	bool isValidInd(int index);
	bool isEmpty(void);
	// Virtual getter function to access the static variables in every class (they differ by value)
	virtual int getMaxCardAmount(void) const = 0;
	bool isFull(void);

	MinionCard getByInd(int index);
	// Battlefield / Hand classes
	MinionCard delByInd(int index);
};

#endif // BASECARD_H_INCLUDED