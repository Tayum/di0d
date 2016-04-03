#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

class MinionCard {	//CHANGE TO CARD, + MINION/SPELL
	char * cardName;
	int attack;
	int health;
	int manacost;
	int taunt;
public:
	int curHealth;
	int curAttack;

	MinionCard() {
		cardName = "NoName";
		attack = 0;
		health = 0;
		manacost = 0;
		taunt = 0;
		curHealth = 0;
		curAttack = 0;
	}
	MinionCard(char * cardName, int attack, int health, int manacost, int taunt) {
		this->cardName = cardName;
		this->attack = attack;
		this->health = health;
		this->manacost = manacost;
		this->taunt = taunt;
		curHealth = health;
		curAttack = attack;
	}

	void printMinionCard() {
		printf("=====%s=====\n", cardName);
		printf("ATTACK: %i\n", attack);
		printf("HEALTH: %i\n", health);
		printf("MANA COST: %i\n", manacost);
		printf("TAUNT: %i\n", taunt);
		printf("CURRENT ATTACK: %i\n", curAttack);
		printf("CURRENT HEALTH: %i\n", curHealth);
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
	SpellCard() {
		cardName = "NoName";
		manacost = 0;
		desc = "NoDesc";
	}
	SpellCard(char * cardName, int manacost, char * desc) {
		this->cardName = cardName;
		this->manacost = manacost;
		this->desc = desc;
	}

	//some funcs
};

class Deck {	//CHECK IF WORKS
	int maxCardAmount;
	int curCardAmount;
	int firstCard;
	int lastCard;
	MinionCard * chain;	//CARD AT ALL
public:
	Deck() {
		maxCardAmount = 0;
		curCardAmount = 0;
		firstCard = 0;
		lastCard = 0;
		chain = NULL;
	}

	Deck(int size) {
		maxCardAmount = size;
		firstCard = 0;
		lastCard = 0;
		curCardAmount = size;
		chain = new MinionCard[maxCardAmount];	//CARD AT ALL
	}
	~Deck() {
		delete[] chain;
	}

	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}

	void kneadCardLast(MinionCard card) {	//CARD AT ALL
		if (!isFull()) {
			chain[lastCard] = card;
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard drawCard() {	//CARD AT ALL
		if (isEmpty()) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = chain[firstCard];
			firstCard++;
			curCardAmount--;
			return card;
		}
	}

};

class HandElement {
public:
	MinionCard card;
	HandElement * next;

	HandElement() {
		card = MinionCard();	//CARD AT ALL
		next = NULL;
	}
	~HandElement() {
		delete next;
	}
};

class Hand {
	HandElement firstCard;
	HandElement lastCard;
	int maxCardAmount;
	int curCardAmount;
public:
	Hand() {
		firstCard = HandElement();
		lastCard = HandElement();
		maxCardAmount = 0;
		curCardAmount = 0;
	}
	Hand(int size) {
		firstCard = HandElement();
		lastCard = HandElement();
		maxCardAmount = size;
		curCardAmount = 0;
	}

	void drawCard(MinionCard card) {
		HandElement newElement = HandElement();
		newElement.card = card;
		if (&lastCard == NULL) {	//CHECK IF WORKS
			firstCard = newElement;
			lastCard = newElement;
		}
		else {
			lastCard.next = &newElement; 	//CHECK IF WORKS
			lastCard = newElement;
		}
		curCardAmount++;
	}

	//ADD DEL_EL
	//ADD GET_EL
	//ADD GET_SIZE
	//ADD IS_EMPTY

};

void cardTrading(MinionCard &cardAttacker, MinionCard &cardDefender) {
	cardAttacker.chngHealth(cardAttacker.curHealth - cardDefender.curAttack);
	cardDefender.chngHealth(cardDefender.curHealth - cardAttacker.curAttack);
	cardAttacker.chngAttack(cardAttacker.curAttack - 1);
	cardDefender.chngAttack(cardDefender.curAttack - 1);
}

int main(void) {
	MinionCard ogre = MinionCard("ogre", 6, 7, 6, 0);
	MinionCard guardTree = MinionCard("guardTree", 5, 10, 7, 0);
	ogre.printMinionCard();
	guardTree.printMinionCard();
	cardTrading(ogre, guardTree);
	ogre.printMinionCard();
	guardTree.printMinionCard();
	getch();
	return 0;
}



/*class Hero {

char * heroName;
int health;
int curHealth;
HeroPower myHeroPower;
public:
Hero(char * heroName) {
health = 30;
curHealth = 30;
myHeroPower = HeroPower("Jaina");

}
};

class HeroPower {
char * heroPowerName;
const int manacost = 2;
char * desc;
public:
HeroPower(char * name) {
this->heroPowerName = name;
desc = "Jaina";
}
};*/