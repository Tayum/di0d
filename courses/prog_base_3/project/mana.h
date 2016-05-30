#ifndef MANA_H_INCLUDED
#define MANA_H_INCLUDED

#include "minionCard.h"

// Implemented in hand class
class Mana {
	static const int MAX_MANA = 10;
	int curMana;
	int curMaxMana;
public:
	Mana();

	int getCurMana(void);
	int getCurMaxMana(void);
	bool isEnough(MinionCard card);
	bool isEnough(int reqMana);
	void useCard(MinionCard card);
	void useHeroPower(void);
	void onTurnStart(void);

private:
	void manaGrow(void);
	void manaReplenish(void);
};

#endif // MANA_H_INCLUDED
