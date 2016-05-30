#include <iostream>
#include <sstream>
#include <list>
#include <vector>

#include <time.h>

#include "background.h"
#include "menu.h"
#include "picture.h"
#include <SFML/Audio.hpp>

#define ALL_CARDS 16

typedef enum {
	HAND = 1,
	BF,
	HERO,
	HERO_POWER
} clickType;

using namespace std;
using namespace sf;

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

	MinionCard() {
		/*Picture pic = Picture("shadowOfNothing.png", 0, 0, 286, 395);
		this->pic = &pic;*/
		pic = nullptr;
		cardName = "NoName";
		attack = 0;
		curAttack = 0;
		health = 0;
		curHealth = 0;
		manacost = 0;
		taunt = false;
		attacked = true;
	}
	MinionCard(Picture * pic, std::string cardName, int attack, int health, int manacost, bool taunt) {
		this->pic = pic;
		this->cardName = cardName;
		this->attack = attack;
		curAttack = attack;
		this->health = health;
		curHealth = health;
		this->manacost = manacost;
		this->taunt = taunt;
		attacked = true;
	}

	int getManacost(void) {
		return manacost;
	}

	int getCurAttack(void) {
		return curAttack;
	}

	int getCurHealth(void) {
		return curHealth;
	}

	bool getTaunt(void) {
		return taunt;
	}

	bool hasAttacked(void) {
		return attacked;
	}

	void setCurHealth(int newHealth) {
		curHealth = newHealth;
	}

	void setCurAttack(int newAttack) {
		curAttack = newAttack;
	}

	void setHasAttacked(bool hasAttacked) {
		attacked = hasAttacked;
	}

	void attackCard(MinionCard  * cardDefender) {
		curHealth -= cardDefender->curAttack;
		cardDefender->curHealth -= curAttack;
		attacked = true;
	}

};

// (it's actually STACK, it's not deck!)
class Deck {
	static const int MAX_CARD_AMOUNT = 30;
	int curCardAmount;
	int lastCard;
	MinionCard * cardList;
public:
	Deck() {
		lastCard = 0;
		curCardAmount = 0;
		cardList = new MinionCard[MAX_CARD_AMOUNT];
	}
	~Deck() {
		delete[] cardList;
	}

	int getCurCardAmount(void) {
		return curCardAmount;
	}

	void pushLast(MinionCard card) {
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

	MinionCard getByInd(int index) {
		if (!isValidInd(index)) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			return card;
		}
	}

	MinionCard popLast(void) {
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

	void prepare(MinionCard arr[ALL_CARDS]) {
		int counterArr[ALL_CARDS];
		for (int i = 0; i < ALL_CARDS; i++) {
			counterArr[i] = 0;
		}
		for (int i = 0; i < MAX_CARD_AMOUNT; i++) {
			int randNum = rand() % ALL_CARDS;
			if (counterArr[randNum] == 2) {
				i--;
				continue;
			}
			counterArr[randNum]++;

			MinionCard minBuff = arr[randNum];
			minBuff.pic = new Picture();
			memcpy(minBuff.pic, arr[randNum].pic, sizeof(Picture));
			pushRand(minBuff);

		}
	}

	void repickPlayer(bool chng[4], int isFirst) {
		int indeces[4] = { -1,-1,-1,-1 };
		bool isValid;
		for (int i = 0; i < 4 - isFirst; i++) {
			isValid = true;
			if (chng[i]) {
				int index = rand() % 30;
				if (index >= 26 + isFirst) {
					i--;
					continue;
				}
				for (int j = 0; j < 4; j++) {
					if (indeces[j] == index) {
						i--;
						isValid = false;
						break;
					}
				}
				if (isValid) {
					MinionCard temp = cardList[29 - i];
					cardList[29 - i] = cardList[index];
					cardList[index] = temp;
					indeces[i] = index;
				}
			}
		}
	}

	void repickComp(int isFirst) {
		// What cards to repick
		bool chng[4] = { false,false,false,false };
		for (int i = 0; i < 4 - isFirst; i++) {
			if (cardList[29 - i].getManacost() >= 5) {
				chng[i] = true;
			}
		}
		// Actual repicking
		int indeces[4] = { -1,-1,-1,-1 };
		bool isValid;
		for (int i = 0; i < 4 - isFirst; i++) {
			isValid = true;
			if (chng[i]) {
				int index = rand() % 30;
				if (index >= 26 + isFirst) {
					i--;
					continue;
				}
				for (int j = 0; j < 4; j++) {
					if (indeces[j] == index) {
						i--;
						isValid = false;
						break;
					}
				}
				if (isValid) {
					MinionCard temp = cardList[29 - i];
					cardList[29 - i] = cardList[index];
					cardList[index] = temp;
					indeces[i] = index;
				}
			}
		}
	}

private:
	bool isValidInd(int index) {
		return (index >= 0 && index < curCardAmount);
	}

	bool isEmpty(void) {
		return curCardAmount == 0;
	}

	bool isFull(void) {
		return curCardAmount == MAX_CARD_AMOUNT;
	}
};

// Implemented in hand class
class Mana {
	static const int MAX_MANA = 10;
	int curMana;
	int curMaxMana;
public:
	Mana() {
		curMana = 0;
		curMaxMana = 0;
	}

	int getCurMana(void) {
		return curMana;
	}

	int getCurMaxMana(void) {
		return curMaxMana;
	}

	bool isEnough(MinionCard card) {
		return curMana >= card.getManacost();
	}
	bool isEnough(int reqMana) {
		return curMana >= reqMana;
	}

	void useCard(MinionCard card) {
		if (isEnough(card)) {
			curMana -= card.getManacost();
		}
	}
	void useHeroPower(void) {
		if (isEnough(2)) {
			curMana -= 2;
		}
	}

	void onTurnStart(void) {
		manaGrow();
		manaReplenish();
	}

private:
	void manaGrow(void) {
		if (curMaxMana != MAX_MANA) {
			curMaxMana++;
		}
	}

	void manaReplenish(void) {
		curMana = curMaxMana;
	}
};

class Hand {
	static const int MAX_CARD_AMOUNT = 10;
	int curCardAmount;
	int lastCard;
public:
	MinionCard * cardList;
	Mana mana;

	Hand() {
		lastCard = 0;
		curCardAmount = 0;
		cardList = new MinionCard[MAX_CARD_AMOUNT];
		mana = Mana();
	}
	~Hand() {
		delete[] cardList;
	}

	int getCurCardAmount(void) {
		return curCardAmount;
	}

	void addLast(MinionCard card) {
		if (!isFull()) {
			cardList[lastCard] = card;
			cardList[lastCard].pic->sprite.setScale(0.405, 0.425);
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard getByInd(int index) {
		if (!isValidInd(index)) {
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
		if (!isValidInd(index)) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			lastCard--;
			curCardAmount--;
			return card;
		}
	}


	bool isEmpty() {
		return curCardAmount == 0;
	}

	bool isValidInd(int index) {
		return (index >= 0 && index < curCardAmount);
	}

private:
	bool isFull() {
		return curCardAmount == MAX_CARD_AMOUNT;
	}

};

class Battlefield {
	static const int MAX_CARD_AMOUNT = 7;
	int curCardAmount;
	int lastCard;
public:
	MinionCard * cardList;

	Battlefield() {
		curCardAmount = 0;
		lastCard = 0;
		cardList = new MinionCard[MAX_CARD_AMOUNT];
	}
	~Battlefield() {
		delete[] cardList;
	}

	int getCurCardAmount(void) {
		return curCardAmount;
	}

	void addLast(MinionCard card) {
		if (!isFull()) {
			cardList[lastCard] = card;
			cardList[lastCard].pic->sprite.setScale(0.671, 0.405);
			lastCard++;
			curCardAmount++;
		}
	}

	MinionCard getByInd(int index) {
		if (!isValidInd(index)) {
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
		if (!isValidInd(index)) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			MinionCard card = cardList[index];
			for (i = index; i < curCardAmount - 1; i++) {
				cardList[i] = cardList[i + 1];
			}
			lastCard--;
			curCardAmount--;
			return card;
		}
	}

	void checkDead(void) {
		for (int i = 0; i < curCardAmount; i++) {
			if (cardList[i].getCurHealth() <= 0) {
				delByInd(i);
				break;
			}
		}
	}

	bool isValidInd(int index) {
		return (index >= 0 && index < curCardAmount);
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
		return curCardAmount == MAX_CARD_AMOUNT;
	}
private:
	bool isEmpty() {
		return curCardAmount == 0;
	}
};

class Hero {
	static const int MAX_HP = 30;
	int curHP;
	std::string name;
	bool usedHeroPower;
public:
	Picture * pic;

	Hero(std::string name, Picture * pic) {
		curHP = MAX_HP;
		usedHeroPower = false;
		this->name = name;
		this->pic = pic;
	}

	int getCurHP(void) {
		return curHP;
	}

	std::string getName(void) {
		return name;
	}

	void setCurHP(int newHP) {
		curHP = newHP;
	}

	bool hasUsedHeroPower(void) {
		return usedHeroPower;
	}

	void setHasUsedHeroPower(bool hasUsedHeroPower) {
		usedHeroPower = hasUsedHeroPower;
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
	Hand hand;	// Mana class is inside
	Battlefield bf;
	Turn turn;
	Hero hero;

	Player(std::string heroName, Picture * heroPic)
		: deck(), hand(), bf(), hero(heroName, heroPic) {
		//deck = Deck();
		//hand = Hand();
		//bf = Battlefield();
		turn = Turn();
	}
	Player(Deck deck, Hand hand, Battlefield battlefield, Hero hero) : hero(hero) {
		this->deck = deck;
		this->hand = hand;
		this->bf = battlefield;
		//this->hero = hero;
		turn = Turn();
	}

	void drawCard() {
		MinionCard card = deck.popLast();
		if (card.getCurHealth() != 0) {
			hand.addLast(card);
		}
	}

	void playCard(int indexHand) {
		if (!bf.isFull() && hand.isValidInd(indexHand) && hand.mana.isEnough(hand.cardList[indexHand])) {
			MinionCard card = hand.delByInd(indexHand);
			hand.mana.useCard(card);
			bf.addLast(card);
		}
	}

	void startTurn() {
		turn.start();
		hand.mana.onTurnStart();
		for (int i = 0; i < bf.getCurCardAmount(); i++) {
			bf.cardList[i].setHasAttacked(false);
		}
		hero.setHasUsedHeroPower(false);
		drawCard();
	}

	void endTurn() {
		turn.end();
	}

};

// GENERAL FUNCTIONS
void attack(Player * human, Player * computer, int cardAttackerInd, int cardDefenderInd) {
	if (human->turn.isTurn() && !computer->turn.isTurn()) { // if it's human turn
		if (human->bf.isValidInd(cardAttackerInd) && computer->bf.isValidInd(cardDefenderInd)) {
			if (human->bf.cardList[cardAttackerInd].hasAttacked() == false) {
				if (computer->bf.isThereTaunts() == computer->bf.cardList[cardDefenderInd].getTaunt()) {
					human->bf.cardList[cardAttackerInd].attackCard(&computer->bf.cardList[cardDefenderInd]);
					human->bf.checkDead();
					computer->bf.checkDead();
				}
			}
		}
	}
	else if (computer->turn.isTurn() && !human->turn.isTurn()) { // if it's computer turn
		if (computer->bf.isValidInd(cardAttackerInd) && human->bf.isValidInd(cardDefenderInd)) {
			if (computer->bf.cardList[cardAttackerInd].hasAttacked() == false) {
				if (human->bf.isThereTaunts() == human->bf.cardList[cardDefenderInd].getTaunt()) {
					computer->bf.cardList[cardAttackerInd].attackCard(&human->bf.cardList[cardDefenderInd]);
					computer->bf.checkDead();
					human->bf.checkDead();
				}
			}
		}
	}
}

void attack(Player * human, Player * computer, int cardAttackerInd) {
	if (human->turn.isTurn() && !computer->turn.isTurn()) { // if it's human turn
		if (human->bf.isValidInd(cardAttackerInd)) {
			if (human->bf.cardList[cardAttackerInd].hasAttacked() == false) {
				if (computer->bf.isThereTaunts() == false) {
					computer->hero.setCurHP(computer->hero.getCurHP() - human->bf.cardList[cardAttackerInd].getCurAttack());
					human->bf.cardList[cardAttackerInd].setHasAttacked(true);
				}
			}
		}
	}
	else if (computer->turn.isTurn() && !human->turn.isTurn()) { // if it's computer turn
		if (computer->bf.isValidInd(cardAttackerInd)) {
			if (computer->bf.cardList[cardAttackerInd].hasAttacked() == false) {
				if (human->bf.isThereTaunts() == false) {
					human->hero.setCurHP(human->hero.getCurHP() - computer->bf.cardList[cardAttackerInd].getCurAttack());
					computer->bf.cardList[cardAttackerInd].setHasAttacked(true);
				}
			}
		}
	}
}

void useHeroPower(Player * human, Player * computer) {
	if (human->turn.isTurn() && !computer->turn.isTurn()) { // if it's human turn
		if (human->hero.hasUsedHeroPower() == false) {
			if (human->hand.mana.isEnough(2)) {
				human->hand.mana.useHeroPower();
				computer->hero.setCurHP(computer->hero.getCurHP() - 1);
				human->hero.setHasUsedHeroPower(true);
			}
		}
	}
	else if (computer->turn.isTurn() && !human->turn.isTurn()) { // if it's computer turn
		if (computer->hero.hasUsedHeroPower() == false) {
			if (computer->hand.mana.isEnough(2)) {
				computer->hand.mana.useHeroPower();
				human->hero.setCurHP(human->hero.getCurHP() - 1);
				computer->hero.setHasUsedHeroPower(true);
			}
		}
	}
}

void useHeroPower(Player * human, Player * computer, int cardDefenderInd) {
	if (human->turn.isTurn() && !computer->turn.isTurn()) { // if it's human turn
		if (computer->bf.isValidInd(cardDefenderInd)) {
			if (human->hero.hasUsedHeroPower() == false) {
				if (human->hand.mana.isEnough(2)) {
					human->hand.mana.useHeroPower();
					computer->bf.cardList[cardDefenderInd].setCurHealth(computer->bf.cardList[cardDefenderInd].getCurHealth() - 1);
					computer->bf.checkDead();
					human->hero.setHasUsedHeroPower(true);
				}
			}
		}
	}
	else if (computer->turn.isTurn() && !human->turn.isTurn()) { // if it's computer turn
		if (human->bf.isValidInd(cardDefenderInd)) {
			if (computer->hero.hasUsedHeroPower() == false) {
				if (computer->hand.mana.isEnough(2)) {
					computer->hand.mana.useHeroPower();
					human->bf.cardList[cardDefenderInd].setCurHealth(human->bf.cardList[cardDefenderInd].getCurHealth() - 1);
					human->bf.checkDead();
					computer->hero.setHasUsedHeroPower(true);
				}
			}
		}
	}
}

void endTurn(Player * human, Player * computer) {
	if (human->turn.isTurn() && !computer->turn.isTurn()) { // if it's human turn
		human->endTurn();
		computer->startTurn();
	}
	else if (computer->turn.isTurn() && !human->turn.isTurn()) { // if it's computer turn
		computer->endTurn();
		human->startTurn();
	}
}

void startGame(Player * human, Player * computer) {
	int isHumanFirst = rand() % 2;
	computer->deck.repickComp(1 - isHumanFirst);
	//human->deck.repickPlayer(boolArr, isPlayerFirst)
	for (int i = 0; i < 3; i++) {
		human->drawCard();
		computer->drawCard();
	}
	if (isHumanFirst == 1) {
		computer->drawCard();
		human->startTurn();
	}
	else {
		human->drawCard();
		computer->startTurn();
	}
}

int main(void) {
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(1344, 640), "Candlehearth", sf::Style::Fullscreen);	//CREATING A WINDOW (1366*768 is native)
	Clock clock;
	Picture background = Picture("backgroundTilesets.png", 0, 0, 128, 32);

	//===============FONT
	Font font;
	font.loadFromFile("font/CyrilicOld.TTF");
	Text heroNameEnemy("", font, 20); // 25 for "Jaina"
	Text hpEnemy("", font, 30);
	Text curManaEnemy("", font, 25);
	Text maxManaEnemy("", font, 25);
	Text handEnemy("", font, 25);
	Text deckEnemy("", font, 25);
	Text heroNamePlayer("", font, 25);
	Text hpPlayer("", font, 30);
	Text curManaPlayer("", font, 25);
	Text maxManaPlayer("", font, 25);
	Text handPlayer("", font, 25);
	Text deckPlayer("", font, 25);
	Text bfTextPlayer[7];
	for (int i = 0; i < 7; i++) {
		bfTextPlayer[i] = Text("", font, 18);
		bfTextPlayer[i].setString("ATTACK");
	}
	Text bfHPTextPlayer[7];
	Text bfHPTextEnemy[7];
	for (int i = 0; i < 7; i++) {
		bfHPTextPlayer[i] = Text("", font, 38);
		bfHPTextPlayer[i].setColor(Color::Red);
		bfHPTextPlayer[i].setStyle(Text::Bold);
		bfHPTextEnemy[i] = Text("", font, 38);
		bfHPTextEnemy[i].setColor(Color::Red);
		bfHPTextEnemy[i].setStyle(Text::Bold);
	}
	
	heroNameEnemy.setColor(Color::White);
	hpEnemy.setColor(Color::Red);
	curManaEnemy.setColor(Color::Cyan);
	maxManaEnemy.setColor(Color::Blue);
	handEnemy.setColor(Color::Green);
	deckEnemy.setColor(Color::Yellow);
	heroNamePlayer.setColor(Color::White);
	hpPlayer.setColor(Color::Red);
	curManaPlayer.setColor(Color::Cyan);
	maxManaPlayer.setColor(Color::Blue);
	handPlayer.setColor(Color::Green);
	deckPlayer.setColor(Color::Yellow);
	hpEnemy.setStyle(Text::Bold);
	curManaEnemy.setStyle(Text::Italic);
	maxManaEnemy.setStyle(Text::Bold);
	handEnemy.setStyle(Text::Italic);
	deckEnemy.setStyle(Text::Bold);
	hpPlayer.setStyle(Text::Bold);
	curManaPlayer.setStyle(Text::Italic);
	maxManaPlayer.setStyle(Text::Bold);
	handPlayer.setStyle(Text::Italic);
	deckPlayer.setStyle(Text::Bold);
	//===============FONT_END

	//===============DECK_INIT
	std::string allNames[] = {
		"bloodfenRaptor.png",
		"bootyBayBodyguard.png",
		"boulderfistOgre.png",
		"chillwindYeti.png",
		"coreHound.png",
		"frostwolfGrunt.png",
		"goldshireFootman.png",
		"ironfurGrizzly.png",
		"lordOfTheArena.png",
		"magmaRager.png",
		"murlocRaider.png",
		"oasisSnapjaw.png",
		"riverCrocolisk.png",
		"senjinShieldmasta.png",
		"silverbackPatriarch.png",
		"warGolem.png"
	};
	std::string allCardNames[] = {
		"Bloodfen Raptor",
		"Booty Bay Bodyguard",
		"Boulderfist Ogre",
		"Chillwind Yeti",
		"Core Hound",
		"Frostwolf Grunt",
		"Goldshire Footman",
		"Ironfur Grizzly",
		"Lord of the Arena",
		"Magma Rager",
		"Murloc Raider",
		"Oasis Snapjaw",
		"River Crocolisk",
		"Sen'jin Shieldmasta",
		"Silverback Patriarch",
		"War Golem"
	};
	int allAttack[] = { 3,5,6,4,9,2,1,3,6,5,2,2,2,3,1,7 };
	int allHP[] =	  { 2,4,7,5,5,2,2,3,5,1,1,7,3,5,4,7 };
	int allManacost[] { 2,5,6,4,7,2,1,3,6,3,1,4,2,4,3,7 };
	bool allTaunt[] = { false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,false };
	MinionCard allCards[ALL_CARDS];

	std::list<Picture *>  picList;
	std::list<Picture *>::iterator iterList;
	for (int i = 0; i < ALL_CARDS; i++) {
		picList.push_back(new Picture(allNames[i], 0, 0, 286, 395));
	}
	MinionCard minionBuff;
	int i = 0;
	for (iterList = picList.begin(); iterList != picList.end(); iterList++) {
		minionBuff = MinionCard((*iterList), allCardNames[i], allAttack[i], allHP[i], allManacost[i], allTaunt[i]);
		allCards[i] = minionBuff;
		i++;
	}
	//===============DECK_INIT_END

	// HERO POWER
	Picture fireblast = Picture("fireblast.png", 0, 0, 286, 395);
	fireblast.sprite.setScale(0.447, 0.405);
	fireblast.sprite.setPosition(1056, 0);

	//===============PLAYER_INIT
	Picture picBuffHuman = Picture("jaina.png", 0, 0, 200, 200);
	Player human = Player("Jaina", &picBuffHuman);
	human.hero.pic->sprite.setScale(0.48, 0.48);
	Picture picBuffComp = Picture("guldan.png", 0, 0, 200, 200);
	Player comp = Player("Gul'dan", &picBuffComp);
	comp.hero.pic->sprite.setScale(0.48, 0.48);

	human.deck.prepare(allCards);
	comp.deck.prepare(allCards);
	//===============PLAYER_INIT_END

	//===============TIMER
	float enemyTurnTimer = 0;
	clock.restart();
	//===============TIMER_END

	//===============MOUSE CONTROL
	bool isClicked = false;
	clickType type = HAND;
	int indFirstClick = 0;
	Vector2i mouseClickPos;
	//===============MOUSE CONTROL_END

	//===============ENEMY AI
	bool avlAttacks = true;
	bool avlSummon = true;
	//===============ENEMY AI_END

	//===============START GAME
	startGame(&human, &comp);
	//===============START GAME_END

	// END TURN BUTTON
	Picture endTurnButton = Picture("endTurn.png", 0, 0, 320, 160);
	if (human.turn.isTurn()) {
		endTurnButton.sprite.setTextureRect(IntRect(0, 0, 160, 160));
	}
	else {
		endTurnButton.sprite.setTextureRect(IntRect(160, 0, 160, 160));
	}
	endTurnButton.sprite.setPosition(1184, 0);
	// END TURN BUTTON_END

	//===============MENU
	menu(&window);
	//===============MENU_END

	//===============MUSIC
	Music music;
	music.openFromFile("music/tabletopBattles.ogg");
	music.play();
	music.setLoop(true);
	//===============MUSIC_END

	while (window.isOpen()) { //MAIN CYCLE OF SFML

		float time = clock.getElapsedTime().asMilliseconds(); //receiving passed time (in ms)
		clock.restart(); //restarting clock
		enemyTurnTimer += time;
		//std::cout << keyPressedTimer << "\n"; //showing the time passed in console

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { // if "close" button is clicked - close window
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && human.turn.isTurn()) {
				if (event.key.code == Mouse::Left) { // (LMB)
					mouseClickPos = Mouse::getPosition(window);

					// END TURN BUTTON CLICK
					if (endTurnButton.sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {

						for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
							human.hand.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
							human.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						fireblast.sprite.setColor(Color::White);
						// SWITCHING TO ENEMY TURN BUTTON
						endTurnButton.sprite.setTextureRect(IntRect(160, 0, 160, 160));

						isClicked = false;
						endTurn(&human, &comp);
					}

					// IF THE BUTTON WAS NOT CLICKED BEFORE!
					if (!isClicked) {
						//std::cout << mouseClickPos.x << "\n"; //x coord to console
						// CLICK FOR HERO POWER!
						if (fireblast.sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
							type = HERO_POWER;
							isClicked = true;
							fireblast.sprite.setColor(Color::Green);
						}
						else {
							// CLICK FOR HAND (PLAYER)!
							if (!isClicked) {
								for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
									if (human.hand.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
										//std::cout << "Clicked the hand sprite (first click)!\n"; // print to console the msg about it
										indFirstClick = i;
										type = HAND;
										isClicked = true;
										human.hand.cardList[i].pic->sprite.setColor(Color::Green);
										break;
									}
								}
							}
							if (!isClicked) {
								// CLICK FOR BATTLEFIELD (PLAYER)!
								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									if (human.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
										//std::cout << "Clicked the bf sprite (first click)!\n"; // print to console the msg about it
										indFirstClick = i;
										type = BF;
										isClicked = true;
										human.bf.cardList[i].pic->sprite.setColor(Color::Green);
										break;
									}
								}
							}
						}

					}

					// IF THE BUTTON WAS CLICKED BEFORE!
					if (isClicked) {
						//std::cout << mouseClickPos.x << "\n"; //x coord to console
						if (type == HAND) {
							// CLICK FOR BF (PLAYER)!
							if (IntRect(0, 320, 1344, 160).contains(mouseClickPos.x, mouseClickPos.y)) {
								//std::cout << "Clicked the bf sprite (player) (second click)!\n"; // print to console the msg about it
								human.playCard(indFirstClick);
								isClicked = false;

								for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
									human.hand.cardList[i].pic->sprite.setColor(Color::White);
								}
								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									human.bf.cardList[i].pic->sprite.setColor(Color::White);
								}

								break;
							}
						}

						else if (type == HERO_POWER) {
							// CLICK FOR BF (ENEMY)!
							for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
								if (comp.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
									//std::cout << "Clicked the bf sprite (enemy) (second click)!\n"; // print to console the msg about it
									useHeroPower(&human, &comp, i);
									isClicked = false;

									fireblast.sprite.setColor(Color::White);

									break;
								}
							}
							// CLICK FOR HERO (ENEMY)!
							if (comp.hero.pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
								//std::cout << "Clicked the hero sprite!\n"; // print to console the msg about it
								useHeroPower(&human, &comp);

								fireblast.sprite.setColor(Color::White);

								isClicked = false;
							}
						}

						else if (type == BF) {
							// CLICK FOR BF (ENEMY)!
							for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
								if (comp.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
									//std::cout << "Clicked the bf sprite (enemy) (second click)!\n"; // print to console the msg about it
									attack(&human, &comp, indFirstClick, i);

									for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
										human.bf.cardList[i].pic->sprite.setColor(Color::White);
									}

									isClicked = false;
									break;
								}
							}
							// CLICK FOR HERO (ENEMY)!
							if (comp.hero.pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
								//std::cout << "Clicked the hero sprite!\n"; // print to console the msg about it
								attack(&human, &comp, indFirstClick);

								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									human.bf.cardList[i].pic->sprite.setColor(Color::White);
								}

								isClicked = false;
							}
						}

					}

				}

				if (event.key.code == Mouse::Right) { // (RMB)
					if (isClicked) {

						for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
							human.hand.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
							human.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						fireblast.sprite.setColor(Color::White);

						isClicked = false;
					}
				}

			}

		}
		window.clear(); // clear all the window

		// AI BEHAVIOUR
		if (comp.turn.isTurn()) {
			if (enemyTurnTimer > 500) {
				// ATTACK
				if (avlAttacks) {
					for (int i = 0; i <= comp.bf.getCurCardAmount(); i++) {
						if (i == comp.bf.getCurCardAmount()) {
							avlAttacks = false;
							break;
						}
						else if (comp.bf.cardList[i].hasAttacked() == false) {
							if (human.bf.isThereTaunts()) {
								for (int j = 0; j < human.bf.getCurCardAmount(); j++) {
									if (human.bf.cardList[j].getTaunt()) {
										attack(&human, &comp, i, j);
										break;
									}
								}
							}
							else {
								attack(&human, &comp, i);
								break;
							}
						}
						else {
							continue;
						}
						break;
					}

				}
				// SUMMON CARDS
				else if (avlSummon) {
					int maxMana = -1;
					int maxManaIndex = -1;
					if (comp.bf.isFull() == false && comp.hand.isEmpty() == false) {
						for (int i = 0; i < comp.hand.getCurCardAmount(); i++) {
							if (comp.hand.mana.isEnough(comp.hand.cardList[i].getManacost()) && comp.hand.cardList[i].getManacost() > maxMana) {
								maxMana = comp.hand.cardList[i].getManacost();
								maxManaIndex = i;
							}
						}
						if (maxMana != -1 && maxManaIndex != -1) {
							comp.playCard(maxManaIndex);
						}
						else {
							avlSummon = false;
						}
					}
					else {
						avlSummon = false;
					}

				}
				// END THE TURN
				if (avlAttacks == false && avlSummon == false) {
					avlAttacks = true;
					avlSummon = true;
					// SWITCHING TO END TURN BUTTON
					endTurnButton.sprite.setTextureRect(IntRect(0, 0, 160, 160));

					endTurn(&human, &comp);
				}

				enemyTurnTimer = 0;
			}

		}


		// draw the background
		for (int i = 0; i < HEIGHT_BG; i++) {
			for (int j = 0; j < WIDTH_BG; j++) {
				if (bgTile[i][j] == 'h') {
					background.sprite.setTextureRect(IntRect(96, 0, 32, 32));
				}
				else if (bgTile[i][j] == 'c') {
					background.sprite.setTextureRect(IntRect(64, 0, 32, 32));
				}
				else if ((bgTile[i][j] == 'b')) {
					background.sprite.setTextureRect(IntRect(0, 0, 32, 32));
				}
				else if ((bgTile[i][j] == ' ')) {
					background.sprite.setTextureRect(IntRect(32, 0, 32, 32));
				}
				background.sprite.setPosition(j * 32, i * 32);
				window.draw(background.sprite);
			}
		}

		// draw cards (enemy bf, human bf (with attack state: text, curHP: text), human hand)
		ostringstream buff;
		for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
			comp.bf.cardList[i].pic->sprite.setPosition(192 * i, 160);
			window.draw(comp.bf.cardList[i].pic->sprite);

			buff.str("");
			buff << comp.bf.cardList[i].getCurHealth();
			bfHPTextEnemy[i].setString("" + buff.str());
			bfHPTextEnemy[i].setPosition(192 * i + 158, 278);
			window.draw(bfHPTextEnemy[i]);
		}
		for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
			human.bf.cardList[i].pic->sprite.setPosition(192 * i, 320);
			window.draw(human.bf.cardList[i].pic->sprite);

			if (human.bf.cardList[i].hasAttacked() == false) {
				bfTextPlayer[i].setColor(Color::Green);
			}
			else {
				bfTextPlayer[i].setColor(Color::Red);
			}
			bfTextPlayer[i].setPosition(192 * i + 62, 452);
			window.draw(bfTextPlayer[i]);

			buff.str("");
			buff << human.bf.cardList[i].getCurHealth();
			bfHPTextPlayer[i].setString("" + buff.str());
			bfHPTextPlayer[i].setPosition(192 * i + 158, 438);
			window.draw(bfHPTextPlayer[i]);
		}
		for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
			human.hand.cardList[i].pic->sprite.setPosition(128 * (i + 1), 480);
			window.draw(human.hand.cardList[i].pic->sprite);
		}

		// end turn button
		window.draw(endTurnButton.sprite);
		// hero power
		window.draw(fireblast.sprite);

		// draw hero: portrait / name
		// enemy
		comp.hero.pic->sprite.setPosition(32, 32);
		window.draw(comp.hero.pic->sprite);

		buff.str("");
		buff << comp.hero.getName();
		heroNameEnemy.setString("" + buff.str());
		heroNameEnemy.setPosition(32, 0);
		window.draw(heroNameEnemy);
		// human
		human.hero.pic->sprite.setPosition(32, 512);
		window.draw(human.hero.pic->sprite);

		buff.str("");
		buff << human.hero.getName();
		heroNamePlayer.setString("" + buff.str());
		heroNamePlayer.setPosition(32, 480);
		window.draw(heroNamePlayer);

		// draw text: hp/mana/cards
		// enemy
		buff.str("");
		buff << comp.hero.getCurHP();
		hpEnemy.setString("" + buff.str());
		hpEnemy.setPosition(0, 0);

		buff.str("");
		buff << comp.hand.mana.getCurMana();
		curManaEnemy.setString("" + buff.str());
		curManaEnemy.setPosition(0, 64);

		buff.str("");
		buff << comp.hand.mana.getCurMaxMana();
		maxManaEnemy.setString("" + buff.str());
		maxManaEnemy.setPosition(0, 128);

		buff.str("");
		buff << comp.hand.getCurCardAmount();
		handEnemy.setString("" + buff.str());
		handEnemy.setPosition(96, 0);

		buff.str("");
		buff << comp.deck.getCurCardAmount();
		deckEnemy.setString("" + buff.str());
		deckEnemy.setPosition(96, 128);
		// human
		buff.str("");
		buff << human.hero.getCurHP();
		hpPlayer.setString("" + buff.str());
		hpPlayer.setPosition(0, 480);

		buff.str("");
		buff << human.hand.mana.getCurMana();
		curManaPlayer.setString("" + buff.str());
		curManaPlayer.setPosition(0, 544);

		buff.str("");
		buff << human.hand.mana.getCurMaxMana();
		maxManaPlayer.setString("" + buff.str());
		maxManaPlayer.setPosition(0, 608);

		buff.str("");
		buff << human.hand.getCurCardAmount();
		handPlayer.setString("" + buff.str());
		handPlayer.setPosition(96, 480);

		buff.str("");
		buff << human.deck.getCurCardAmount();
		deckPlayer.setString("" + buff.str());
		deckPlayer.setPosition(96, 608);

		window.draw(hpEnemy);
		window.draw(curManaEnemy);
		window.draw(maxManaEnemy);
		window.draw(handEnemy);
		window.draw(deckEnemy);
		window.draw(hpPlayer);
		window.draw(curManaPlayer);
		window.draw(maxManaPlayer);
		window.draw(handPlayer);
		window.draw(deckPlayer);

		window.display();		//display all the window.draw's
	}
	// end of program
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