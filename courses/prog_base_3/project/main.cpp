#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>

using namespace std;

//everything seems working fine
class MinionCard {	//CHANGE TO CARD, + MINION/SPELL
	char * cardName;
	int attack;
	int health;
	int manacost;
	bool taunt;
	int curHealth;
	int curAttack;
public:
	MinionCard() {
		cardName = "NoName";
		attack = 0;
		health = 0;
		manacost = 0;
		taunt = false;
		curHealth = 0;
		curAttack = 0;
	}
	MinionCard(char * cardName, int attack, int health, int manacost, bool taunt) {
		this->cardName = cardName;
		this->attack = attack;
		this->health = health;
		this->manacost = manacost;
		this->taunt = taunt;
		curHealth = health;
		curAttack = attack;
	}

	int getManacost() {
		return manacost;
	}

	int getCurAttack() {
		return curAttack;
	}

	int getCurHealth() {
		return curHealth;
	}

	bool getTaunt() {
		return taunt;
	}

	void setCurHealth(int newHealth) {
		curHealth = newHealth;
	}

	void setCurAttack(int newAttack) {
		curAttack = newAttack;
	}

	void attackCard(MinionCard &cardDefender) {
		setCurHealth(this->curHealth - cardDefender.curAttack);
		cardDefender.setCurHealth(cardDefender.curHealth - this->curAttack);
	}

	void printMinionCard() {
		printf("=====%s=====\n", cardName);
		printf("ATTACK: %i\n", attack);
		printf("HEALTH: %i\n", health);
		printf("MANA COST: %i\n", manacost);
		if (taunt) {
			puts("TAUNT: +");
		}
		else {
			puts("TAUNT: -");
		}
		printf("CURRENT ATTACK: %i\n", curAttack);
		printf("CURRENT HEALTH: %i\n", curHealth);
		puts("");
	}

	/*void heroTrading(MinionCard cardAttacker, Hero heroDefender) {
	//hero.health-=cardAttacker.curAttack;
	}*/
};

/*
=====SPELL CLASS CARD (raw)=====
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
};*/

//everything seems working fine
//(it's STACK, it's not deck!)
class Deck {
	int maxCardAmount;
	int curCardAmount;
	int firstCard;
	int lastCard;
	MinionCard * cardList;	//CARD AT ALL
public:
	Deck() {
		maxCardAmount = 0;
		curCardAmount = 0;
		firstCard = 0;
		lastCard = 0;
		cardList = NULL;
	}
	Deck(int size) {
		maxCardAmount = size;
		firstCard = 0;
		lastCard = 0;
		curCardAmount = 0;
		cardList = new MinionCard[maxCardAmount];	//CARD AT ALL
	}
	~Deck() {
		printf("Desctructor of DECK\n");
		delete[] cardList;
	}

	void push(MinionCard card) {	//CARD AT ALL
		if (!isFull()) {
			cardList[lastCard] = card;
			lastCard++;
			curCardAmount++;
		}
	}

	void pushRand(MinionCard card) {
		int index;
		if (!isFull()) {
			if (curCardAmount == 0) {
				cardList[lastCard] = card;
				lastCard++;
				curCardAmount++;
			}
			else {
				index = rand() % curCardAmount;
				if (index == lastCard) {
					cardList[lastCard] = card;
					lastCard++;
					curCardAmount++;
				}
				else {
					for (int i = lastCard; i > index; i--) {
						cardList[i] = cardList[i - 1];
					}
					cardList[index] = card;
					lastCard++;
					curCardAmount++;
				}
			}
		}
	}

	MinionCard pop() {	//CARD AT ALL
		if (isEmpty()) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = cardList[lastCard - 1];	//CARD AT ALL
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	MinionCard peek() {	//CARD AT ALL
		if (isEmpty()) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = cardList[lastCard - 1];	//CARD AT ALL
			return card;
		}
	}

	void printCards() {
		for (int i = 0; i < curCardAmount; i++) {
			cardList[i].printMinionCard();
		}
	}

private:
	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}
};
//FOR HAND CLASS! (+ probably turn class?)
class Mana {
	int curMana;
	int curMaxMana;
	int maxMana;
public:
	Mana() {
		curMana = 0;
		curMaxMana = 0;
		maxMana = 0;
	}
	Mana(int maxMana) {
		curMana = 0;
		curMaxMana = 0;
		this->maxMana = maxMana;
	}

	bool isEnough(MinionCard card) {
		return curMana <= card.getManacost();
	}

	void useCard(MinionCard card) {
		if (isEnough(card)) {
			curMana -= card.getManacost();
		}
	}

	void startTurn() {
		manaGrow();
		manaReplenish();
	}

private:
	void manaGrow() {
		if (curMaxMana != maxMana) {
			curMaxMana++;
		}
	}

	void manaReplenish() {
		curMana = curMaxMana;
	}
};

//everything seems working fine
class Hand {
	int maxCardAmount;
	int curCardAmount;
	int lastCard;
	MinionCard * cardList;	//CARD AT ALL
public:
	Mana mana;

	Hand() {
		lastCard = 0;
		maxCardAmount = 0;
		curCardAmount = 0;
		cardList = NULL;
		mana = Mana();
	}
	Hand(int size, int manaCap) {
		lastCard = 0;
		maxCardAmount = size;
		curCardAmount = 0;
		cardList = new MinionCard[maxCardAmount];	//CARD AT ALL
		mana = Mana(manaCap);
	}
	~Hand() {
		printf("Desctructor of HAND\n");
		delete[] cardList;
	}

	void addLast(MinionCard card) {	//CARD AT ALL
		if (!isFull()) {
			cardList[lastCard] = card;
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard getByInd(int index) {	//CARD AT ALL
		int i;
		if (isEmpty() || index >= curCardAmount || index < 0) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = cardList[index];	//CARD AT ALL
			return card;
		}
	}

	MinionCard delByInd(int index) {	//CARD AT ALL
		int i;
		if (isEmpty() || index >= curCardAmount || index < 0 || !mana.isEnough(cardList[index])) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			mana.useCard(cardList[index]);
			MinionCard card = cardList[index];	//CARD AT ALL
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			cardList[i] = MinionCard();	//CARD AT ALL
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	void printCards() {
		for (int i = 0; i < curCardAmount; i++) {
			cardList[i].printMinionCard();
		}
	}

private:
	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}

};

class Battlefield : public MinionCard {
	int maxCardAmount;
	int curCardAmount;
	int firstCard;
	int lastCard;
public:
	MinionCard * cardList;

	Battlefield() {
		maxCardAmount = 0;
		curCardAmount = 0;
		firstCard = 0;
		lastCard = 0;
		cardList = NULL;
	}
	Battlefield(int size) {
		maxCardAmount = size;
		curCardAmount = 0;
		firstCard = 0;
		lastCard = 0;
		cardList = new MinionCard[size];
	}
	~Battlefield() {
		printf("Desctructor of BF\n");
		delete[] cardList;
	}

	void addLast(MinionCard card) {
		if (!isFull()) {
			cardList[lastCard] = card;
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard getByInd(int index) {
		int i;
		if (isEmpty() || !isValidInd(index)) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = cardList[index];	//CARD AT ALL
			return card;
		}
	}

	MinionCard delByInd(int index) {
		int i;
		if (isEmpty() || !isValidInd(index)) {
			MinionCard card = MinionCard();	//CARD AT ALL
			return card;
		}
		else {
			MinionCard card = cardList[index];	//CARD AT ALL
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			cardList[i] = MinionCard();	//CARD AT ALL
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	void printCards() {
		for (int i = 0; i < curCardAmount; i++) {
			cardList[i].printMinionCard();
		}
	}

	bool isValidInd(int index) {
		return (index >= 0 && index <= curCardAmount);
	}

	bool isThereTaunts() {
		for (int i = 0; i < curCardAmount; i++) {
			if (cardList[i].getTaunt()) {
				return true;
			}
		}
		return false;
	}

private:
	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}
};

class Turn {
	bool turn;
public:
	Turn() {
		turn = false;
	}

	void start() {
		turn = true;
	}

	void end() {
		turn = false;
	}

	bool isTurn() {
		return turn;
	}
};

class Player {	//public Deck, public Hand, public Battlefield (lel?)
public:
	Deck deck;
	Hand hand;
	Battlefield bf;
	Turn turn;	//+mana
				//add hero!
	Player() {
		deck = Deck();
		hand = Hand();
		bf = Battlefield();
		turn = Turn();
	}
	Player(Deck deck, Hand hand, Battlefield battlefield) {
		this->deck = deck;
		this->hand = hand;
		this->bf = battlefield;
		turn = Turn();
	}
	Player(int deckCap, int handCap, int manaCap, int battlefieldCap) {
		deck = Deck(deckCap);
		hand = Hand(handCap, manaCap);
		bf = Battlefield(battlefieldCap);
		turn = Turn();
	}

	void drawCard() {
		MinionCard card = deck.pop();
		hand.addLast(card);
	}

	void playCard(int indexHand) {		//in late advance: add this func to Game class?
		MinionCard card = hand.delByInd(indexHand);
		hand.mana.useCard(card);
		bf.addLast(card);
	}

	void startTurn() {
		turn.start();
		hand.mana.startTurn();
		drawCard();
	}

	void endTurn() {
		turn.end();
	}

};

class Game {
	Player firstPlayer;
	Player secondPlayer;
public:
	Game() {
		firstPlayer = Player();
		secondPlayer = Player();
	}
	Game(Player firstPlayer, Player secondPlayer) {
		this->firstPlayer = firstPlayer;
		this->secondPlayer = secondPlayer;
	}

	void attack(int cardAttackerInd, int cardDefenderInd) {
		if (firstPlayer.bf.isValidInd(cardAttackerInd) && secondPlayer.bf.isValidInd(cardDefenderInd)) {
			if (secondPlayer.bf.cardList[cardDefenderInd].getTaunt() == secondPlayer.bf.isThereTaunts()) {
				firstPlayer.bf.cardList[cardAttackerInd].attackCard(secondPlayer.bf.cardList[cardDefenderInd]);
			}
		}
	}

	void endTurn(Player &playerToEnd, Player &playerToStart) {	//???
		playerToEnd.endTurn();
		playerToStart.startTurn();
	}

};

int main(void) {
	srand(time(NULL));
	Player firstPlayer = Player(10, 10, 10, 7);
	Player secondPlayer = Player(10, 10, 10, 7);
	MinionCard card;
	card = MinionCard("Murloc Raider", 2, 1, 1, false);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	getch();
	return 0;
}


//FOR FUTURE TESTS
	/*card = MinionCard("Magma Rager", 5, 1, 3, false);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Lord of the Arena", 6, 5, 6, true);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("War Golem", 7, 7, 7, false);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Core Hound", 9, 5, 7, false);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("River Crocolisk", 2, 3, 2, false);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	card = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
	firstPlayer.deck.pushRand(card);
	secondPlayer.deck.pushRand(card);
	for (int i = 0; i < 10; i++) {
		puts("\n=====FIRST PLAYER DECK GOES HERE=====");
		firstPlayer.deck.printCards();
		puts("\n=====================================\n");
		puts("\n=====SECOND PLAYER DECK GOES HERE=====");
		secondPlayer.deck.printCards();
		puts("\n======================================\n");
		puts("\n=====FIRST PLAYER HAND GOES HERE=====");
		firstPlayer.hand.printCards();
		puts("\n=====================================\n");
		puts("\n=====SECOND PLAYER HAND GOES HERE=====");
		secondPlayer.hand.printCards();
		puts("\n======================================\n");*/
		/*puts("\n=====FIRST PLAYER BATTLEFIELD GOES HERE=====");
		firstPlayer.bf.printCards();
		puts("\n============================================\n");
		puts("\n=====FIRST PLAYER BATTLEFIELD GOES HERE=====");
		secondPlayer.bf.printCards();
		puts("\n============================================\n");
	}*/

/*
//LIST OF CARDS (NON-TAUNT)
MinionCard murlocRaider= MinionCard("Murloc Raider", 2, 1, 1, false);
MinionCard bloodfenRaptor = MinionCard("Bloodfen Raptor", 3, 2, 2, false);
MinionCard riverCrocolisk = MinionCard("River Crocolisk", 2, 3, 2, false);
MinionCard magmaRager = MinionCard("Magma Rager", 5, 1, 3, false);
MinionCard chillwindYeti = MinionCard("Chillwind Yeti", 4, 5, 4, false);
MinionCard oasisSnapjaw = MinionCard("Oasis Snapjaw", 2, 7, 4, false);
MinionCard boulderfistOgre = MinionCard("Boulderfist Ogre", 6, 7, 6, false);
MinionCard warGolem = MinionCard("War Golem", 7, 7, 7, false);
MinionCard coreHound = MinionCard("Core Hound", 9, 5, 7, false);
//LIST OF CARDS (TAUNT)
MinionCard goldshireFootman = MinionCard("Goldshire Footman", 1, 2, 1, true);
MinionCard frostwolfGrunt = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
MinionCard ironfurGrizzly = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
MinionCard silverbackPatriarch = MinionCard("Silverback Patriarch", 1, 4, 3, true);
MinionCard senjinShieldmasta = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
MinionCard bootyBayBodyguard = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
MinionCard lordOfTheArena = MinionCard("Lord of the Arena", 6, 5, 6, true);*/

/*
=====BATTLEFIELD TEST=====
Battlefield myBF = Battlefield(7);
myBF.addLast(ogre);
myBF.printCards();
myBF.addLast(guardTree);
myBF.printCards();
myBF.delByInd(1);
myBF.printCards();
myBF.delByInd(0);
myBF.printCards();*/

/*
=====DECK TEST=====
Deck myDeck = Deck(30);
myDeck.push(ogre);
myDeck.push(guardTree);
MinionCard test = myDeck.pop();
test.printMinionCard();
test= myDeck.pop();
test.printMinionCard();
test = myDeck.pop();
test.printMinionCard();*/

/*
=====HAND TEST=====
Hand myHand = Hand(10, 10);
myHand.addLast(ogre);
myHand.addLast(guardTree);
MinionCard test = myHand.delByInd(0);
test.printMinionCard();
test = myHand.getByInd(1);
test.printMinionCard();
test = myHand.delByInd(0);
test.printMinionCard();
test = myHand.delByInd(0);
test.printMinionCard();*/

/*
=====MINION CARD TEST=====
ogre.printMinionCard();
guardTree.printMinionCard();
ogre.attack(guardTree);
ogre.printMinionCard();
guardTree.printMinionCard();*/


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