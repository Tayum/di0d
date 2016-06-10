#ifndef BATTLEFIELD_H_INCLUDED
#define BATTLEFIELD_H_INCLUDED

#include "baseCard.h"

class Battlefield : public BaseCard {
	static const int MAX_CARD_AMOUNT = 7;
	// Getter function for static variable
	int getMaxCardAmount(void) const;
public:
	Battlefield();
	~Battlefield();

	void addLast(MinionCard card);
	void checkDead(void);
	bool isThereTaunts(void);
};

#endif // BATTLEFIELD_H_INCLUDED