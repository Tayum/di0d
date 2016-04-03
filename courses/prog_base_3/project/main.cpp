#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

class MinionCard {
	char * cardName;
	int attack;
	int health;
	int manacost;
public:
	int curHealth;
	int curAttack;

	MinionCard(char * cardName, int attack, int health, int manacost) {
		this->cardName = cardName;
		this->attack = attack;
		this->health = health;
		this->manacost = manacost;
		curHealth = health;
		curAttack = attack;
	}

	void printMinionCard() {
		printf("=====%s=====\n", this->cardName);
		printf("ATTACK: %i\n", this->attack);
		printf("HEALTH: %i\n", this->health);
		printf("MANA COST: %i\n", this->manacost);
		printf("CURRENT ATTACK: %i\n", this->curAttack);
		printf("CURRENT HEALTH: %i\n", this->curHealth);
		puts("");
	}

	void chngHealth(int newHealth) {
		curHealth = newHealth;
	}
	
	void chngAttack(int newAttack) {
		curAttack = newAttack;
	}

	/*void heroTrading(MinionCard cardAttacker, Hero heroDefender) {
		//hero.health-=cardAttacker.curAttack;
	}*/
};

class SpellCard {
	char * cardName;
	int manacost;
	char * desc;
public:
	SpellCard(char * cardName, int manacost, char * desc) {
		this->cardName = cardName;
		this->manacost = manacost;
		this->desc = desc;
	}

	//some funcs
};

void cardTrading(MinionCard &cardAttacker, MinionCard &cardDefender) {
	cardAttacker.chngHealth(cardAttacker.curHealth - cardDefender.curAttack);
	cardDefender.chngHealth(cardDefender.curHealth - cardAttacker.curAttack);
	cardAttacker.chngAttack(cardAttacker.curAttack - 1);
	cardDefender.chngAttack(cardDefender.curAttack - 1);
}

/*class Hero {
	
	char * heroName;
	int health;
	int curHealth;
	HeroPower myHeroPower;



	Hero(char * heroName) {
		health = 30;
		curHealth = 30;
		myHeroPower;

	}
};

class HeroPower {
	char * heroPowerName;
	const int manacost = 2;
	char * desc;

	HeroPower(char * name) {
		this->heroPowerName = name;
	}
};*/

int main(void) {
	MinionCard ogre = MinionCard("ogre", 6, 7, 6);
	MinionCard guardTree = MinionCard("guardTree", 5, 10, 7);
	ogre.printMinionCard();
	guardTree.printMinionCard();
	cardTrading(ogre, guardTree);
	ogre.printMinionCard();
	guardTree.printMinionCard();
	getch();
	return 0;
}