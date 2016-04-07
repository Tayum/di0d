#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

//everything seems working fine
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

	void cardAttack(MinionCard &cardDefender) {
		chngHealth(this->curHealth - cardDefender.curAttack);
		cardDefender.chngHealth(cardDefender.curHealth - this->curAttack);
		chngAttack(this->curAttack - 1);
		cardDefender.chngAttack(cardDefender.curAttack - 1);
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

//SPELL CLASS CARD (raw)
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

//everything seems working fine
//(it's STACK, it's not deck!)
class Deck {
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
		curCardAmount = 0;
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
			MinionCard card = chain[lastCard - 1];	//CARD AT ALL
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	MinionCard getLastCard() {	//CARD AT ALL
		if (isEmpty()) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = chain[lastCard - 1];	//CARD AT ALL
			return card;
		}
	}

};

//everything seems working fine
class Hand {
	int maxCardAmount;
	int curCardAmount;
	int lastCard;
	MinionCard * chain;	//CARD AT ALL
public:
	Hand() {
		lastCard = 0;
		maxCardAmount = 0;
		curCardAmount = 0;
		chain = NULL;
	}
	Hand(int size) {
		lastCard = 0;
		maxCardAmount = size;
		curCardAmount = 0;
		chain = new MinionCard[maxCardAmount];	//CARD AT ALL
	}
	~Hand() {
		delete[] chain;
	}

	void drawCard(MinionCard card) {	//CARD AT ALL
		if (!isFull()) {
			chain[lastCard] = card;
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard playCard(int index) {	//CARD AT ALL
		int i;
		if (isEmpty() || index >= curCardAmount || index < 0) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = chain[index];	//CARD AT ALL
			for (i = index; i < curCardAmount - 1; i++) {
				chain[i] = chain[i + 1];
			}
			chain[i] = MinionCard();	//CARD AT ALL
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	MinionCard showCard(int index) {	//CARD AT ALL
		int i;
		if (isEmpty() || index >= curCardAmount || index < 0) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = chain[index];	//CARD AT ALL
			return card;
		}
	}

	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}

};

int main(void) {
	MinionCard ogre = MinionCard("ogre", 6, 7, 6, 0);
	MinionCard guardTree = MinionCard("guardTree", 5, 10, 7, 0);
	getch();
	return 0;
}


/*
=====HERO CLASS=====
class Hero {

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

/*
=====HAND USING LIST=====
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

	MinionCard playCard(int index) {	//CARD AT ALL
		MinionCard card;				//CARD AT ALL
		if (&firstCard == NULL) {
			card = MinionCard();	//CARD AT ALL
			return card;
		}
		else if (index < 0 || index >= curCardAmount) {
			card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			if (&firstCard == &lastCard) {
				card = firstCard.card;
				firstCard = HandElement();
				lastCard = HandElement();
			}
			else if (index == 0) {
				card = firstCard.card;
				firstCard.card = firstCard.next->card;	//wtf
				firstCard.next = firstCard.next->next;	//wtf
			}
			else {
				HandElement t = firstCard;
				for (int i = 1; i < index; i++) {
					t.next = t.next->next;	//wtf
				}
				card = t.next->card;
				if (lastCard.next == t.next) {	//wtf
					lastCard = t;
				}
				t.next = t.next->next;
			}
			curCardAmount--;
			return card;
		}
	}

	MinionCard showCard(int index) {	//CARD AT ALL
		MinionCard card;				//CARD AT ALL
		if (&firstCard == NULL) {
			card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			if (&firstCard == &lastCard || index==0) {
				card = firstCard.card;
			}
			else {
				HandElement t = firstCard;
				for (int i = 1; i < index; i++) {
					t.next = t.next->next;	//wtf
				}
				card = t.next->card;
			}
			return card;
		}
	}*/

/*
=====DECK TEST=====
Deck myDeck = Deck(30);
myDeck.kneadCardLast(ogre);
myDeck.kneadCardLast(guardTree);
MinionCard test = myDeck.drawCard();
test.printMinionCard();
test= myDeck.drawCard();
test.printMinionCard();
test = myDeck.drawCard();
test.printMinionCard();*/

/*
=====HAND TEST=====
Hand myHand = Hand(10);
myHand.drawCard(ogre);
myHand.drawCard(guardTree);
MinionCard test = myHand.playCard(0);
test.printMinionCard();
test = myHand.showCard(1);
test.printMinionCard();
test = myHand.playCard(0);
test.printMinionCard();
test = myHand.playCard(0);
test.printMinionCard();*/

/*
=====MINION CARD CLASS TEST=====
ogre.printMinionCard();
guardTree.printMinionCard();
ogre.cardAttack(guardTree);
ogre.printMinionCard();
guardTree.printMinionCard();*/