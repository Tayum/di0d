#ifndef MINIONCARD_H_INCLUDED
#define MINIONCARD_H_INCLUDED

#include "picture.h"

class MinionCard { // -> redo into Card class (minion/spell)
	std::string cardName;
	int attack;
	int curAttack;
	int health;
	int curHealth;
	int manacost;
	bool taunt;
	bool attacked;
public:
	Picture * pic; //variable of class connected with SFML

	MinionCard();
	MinionCard(Picture * pic, std::string cardName, int attack, int health, int manacost, bool taunt);

	int getManacost(void);
	int getCurAttack(void);
	int getCurHealth(void);
	bool getTaunt(void);
	bool hasAttacked(void);
	void setCurHealth(int newHealth);
	void setCurAttack(int newAttack);
	void setHasAttacked(bool hasAttacked);
	void attackCard(MinionCard  * cardDefender);

};

#endif // MINIONCARD_H_INCLUDED
