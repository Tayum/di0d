#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>

using namespace std;

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

	int getHealth() {
		return health;
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

};

//(it's STACK, it's not deck!)
class Deck {
	int maxCardAmount;
	int curCardAmount;
	int firstCard;
	int lastCard;
	MinionCard * cardList;
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
		this->cardList = new MinionCard[maxCardAmount];
	}
	~Deck() {
		printf("Desctructor of DECK\n");
		delete[] cardList;
	}

	void push(MinionCard card) {
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

	MinionCard pop() {
		if (isEmpty()) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[lastCard - 1];
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	MinionCard peek() {
		if (isEmpty()) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[lastCard - 1];
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
		return curMana >= card.getManacost();
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

class Hand {
	int maxCardAmount;
	int curCardAmount;
	int lastCard;
	MinionCard * cardList;
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
		cardList = new MinionCard[maxCardAmount];
		mana = Mana(manaCap);
	}
	~Hand() {
		printf("Desctructor of HAND\n");
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
		if (isEmpty() || index >= curCardAmount || index < 0) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			return card;
		}
	}

	MinionCard delByInd(int index) {
		int i;
		if (isEmpty() || index >= curCardAmount || index < 0 || !mana.isEnough(cardList[index])) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			mana.useCard(cardList[index]);
			MinionCard card = cardList[index];
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			cardList[i] = MinionCard();
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


	bool isEmpty() {
		return curCardAmount == 0;
	}
private:
	bool isFull() {
		return curCardAmount == maxCardAmount;
	}

};

class Battlefield {
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
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			return card;
		}
	}

	MinionCard delByInd(int index) {
		int i;
		if (isEmpty() || !isValidInd(index)) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			cardList[i] = MinionCard();
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

	bool isFull() {
		return curCardAmount == maxCardAmount;
	}
private:
	bool isEmpty() {
		return curCardAmount == 0;
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

class Player {
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
	Player(int deckCap, int handCap, int manaCap, int battlefieldCap) 
		: deck(deckCap), hand(handCap, manaCap), bf(battlefieldCap) {
		//deck = Deck(deckCap);
		//hand = Hand(handCap, manaCap);
		//bf = Battlefield(battlefieldCap);
		turn = Turn();
	}

	void drawCard() {
		MinionCard card = deck.pop();
		if (card.getHealth() != 0) {
			hand.addLast(card);
		}
	}

	void playCard(int indexHand) {		//in late advance: add this func to Game class?
		if (!bf.isFull() && !hand.isEmpty()) {
			MinionCard card = hand.delByInd(indexHand);
			hand.mana.useCard(card);
			bf.addLast(card);
		}
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
	Player firstPlayer(10, 10, 10, 7);
	MinionCard card;

	card = MinionCard("Murloc Raider", 2, 1, 1, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Magma Rager", 5, 1, 3, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Lord of the Arena", 6, 5, 6, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("War Golem", 7, 7, 7, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Core Hound", 9, 5, 7, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("River Crocolisk", 2, 3, 2, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
	firstPlayer.deck.pushRand(card);
	for (int i = 0; i < 11; i++) {
		firstPlayer.startTurn();
	}
	for (int i = 0; i < 11; i++) {
		puts("\n=====FIRST PLAYER HAND GOES HERE=====");
		firstPlayer.hand.printCards();
		puts("\n=====================================\n");
		firstPlayer.playCard(0);
		puts("\n=====FIRST PLAYER BATTLEFIELD GOES HERE=====");
		firstPlayer.bf.printCards();
		puts("\n============================================\n");
		firstPlayer.startTurn();
	}
	getch();
	return 0;
}

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