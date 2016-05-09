#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "background.h"

#define ALL_CARDS 16

using namespace std;
using namespace sf;

//SFML: CLASS OF SPRITE (for MinionCard / map)
class Picture {
	float imgX;	//appear coordinate X
	float imgY;	//appear coordinate Y
	float imgHeight; //height of img
	float imgWidth;	//width of image
	String File;	//name of file with img
	Image image;	//image
	Texture texture;	//texture
public:
	Sprite sprite;	//sprite

	Picture() {
		File = "shadowOfNothing.png";
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		imgWidth = 286;	//width of image
		imgHeight = 395; //height of img
		imgX = 0;
		imgY = 0;
		sprite.setTextureRect(IntRect(0, 0, imgWidth, imgHeight));
	}
	// imageFileName - must be stored in images/ folder
	Picture(String imageFileName, float imgX, float imgY, float imgWidth, float imgHeight) {
		File = imageFileName;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		this->imgWidth = imgWidth;
		this->imgHeight = imgHeight;
		this->imgX = imgX;
		this->imgY = imgY;
		sprite.setTextureRect(IntRect(0, 0, imgWidth, imgHeight));
	}

	//sprite.move(0.1, 0); //move the sprite to +0.1 (x); +0 (y) coordinates

};

class MinionCard { // -> redo into Card class (minion/spell)
	std::string cardName;
	int attack;
	int curAttack;
	int health;
	int curHealth;
	int manacost;
	bool taunt;
public:
	Picture pic; //variable of class connected with SFML

	MinionCard() {
		pic = Picture("shadowOfNothing.png", 0, 0, 286, 395);
		cardName = "NoName";
		attack = 0;
		curAttack = 0;
		health = 0;
		curHealth = 0;
		manacost = 0;
		taunt = false;
	}
	MinionCard(Picture pic, std::string cardName, int attack, int health, int manacost, bool taunt) {
		this->pic = pic;
		this->cardName = cardName;
		this->attack = attack;
		curAttack = attack;
		this->health = health;
		curHealth = health;
		this->manacost = manacost;
		this->taunt = taunt;
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

	void setCurHealth(int newHealth) {
		curHealth = newHealth;
	}

	void setCurAttack(int newAttack) {
		curAttack = newAttack;
	}

	void attackCard(MinionCard  * cardDefender) {
		curHealth -= (*cardDefender).curAttack;
		(*cardDefender).curHealth -= curAttack;
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
		pushRand(arr[randNum]);
		}
	}

private:
	bool isEmpty(void) {
		return curCardAmount == 0;
	}

	bool isFull(void) {
		return curCardAmount == MAX_CARD_AMOUNT;
	}
};

// implemented in hand class (plus in turn class?)
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

	void useCard(MinionCard card) {
		if (isEnough(card)) {
			curMana -= card.getManacost();
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
			cardList[lastCard].pic.sprite.setScale(0.405, 0.425);
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
		if (!isValidInd(index) || !mana.isEnough(cardList[index])) {
			MinionCard card = MinionCard();
			return card;
		}
		else {
			mana.useCard(cardList[index]);
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
			cardList[lastCard].pic.sprite.setScale(0.671, 0.405);
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
	Turn turn;	// mana class is inside
				// add hero!
	Player()
		: deck(), hand(), bf() {
		//deck = Deck();
		//hand = Hand();
		//bf = Battlefield();
		turn = Turn();
	}
	Player(Deck deck, Hand hand, Battlefield battlefield) {
		this->deck = deck;
		this->hand = hand;
		this->bf = battlefield;
		turn = Turn();
	}
	/*
	=====NOT NEEDED BUT CAN BE USEFUL=====
	Player(int deckCap, int handCap, int manaCap, int battlefieldCap)
	: deck(deckCap), hand(handCap, manaCap), bf(battlefieldCap) {
	//deck = Deck(deckCap);
	//hand = Hand(handCap, manaCap);
	//bf = Battlefield(battlefieldCap);
	turn = Turn();
	}*/

	void drawCard() {
		MinionCard card = deck.popLast();
		if (card.getCurHealth() != 0) {
			hand.addLast(card);
		}
	}

	void playCard(int indexHand) {		// (add this func to Game class? (why?) )
		if (!bf.isFull() && hand.isValidInd(indexHand) && hand.mana.isEnough(hand.cardList[indexHand])) {
			MinionCard card = hand.delByInd(indexHand);
			hand.mana.useCard(card);
			bf.addLast(card);
		}
	}

	void startTurn() {
		turn.start();
		hand.mana.onTurnStart();
		drawCard();
	}

	void endTurn() {
		turn.end();
	}

};

class Game {
	Player human;
	Player computer;
public:
	Game() {
		human = Player();
		computer = Player();
	}
	Game(Player human, Player computer) {
		this->human = human;
		this->computer = computer;
	}

	void attack(int cardAttackerInd, int cardDefenderInd) {
		if (human.turn.isTurn() && !computer.turn.isTurn()) { // if it's human turn
			if (human.bf.isValidInd(cardAttackerInd) && computer.bf.isValidInd(cardDefenderInd)) {
				if (computer.bf.isThereTaunts() == computer.bf.cardList[cardDefenderInd].getTaunt()) {
					human.bf.cardList[cardAttackerInd].attackCard(&computer.bf.cardList[cardDefenderInd]);
				}
			}
		}
		else if (computer.turn.isTurn() && human.turn.isTurn()) { // if it's computer turn
			if (computer.bf.isValidInd(cardAttackerInd) && human.bf.isValidInd(cardDefenderInd)) {
				if (human.bf.isThereTaunts() == human.bf.cardList[cardDefenderInd].getTaunt()) {
					computer.bf.cardList[cardAttackerInd].attackCard(&human.bf.cardList[cardDefenderInd]);
				}
			}
		}
	}

	void endTurn(void) {
		if (human.turn.isTurn() && !computer.turn.isTurn()) { // if it's human turn
			human.endTurn();
			computer.startTurn();
		}
		else if (computer.turn.isTurn() && !human.turn.isTurn()) { // if it's computer turn
			computer.endTurn();
			human.startTurn();
		}
	}

};

int main(void) {
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(1344, 640), "Minion Card Test");	//CREATING A WINDOW (1366*768 is native)
	Clock clock;
	Picture map = Picture("backgroundTilesets.png", 0, 0, 128, 32);

	//===============FONT
	Font font;
	font.loadFromFile("font/CyrilicOld.TTF");
	Text hpEnemy("", font, 30);
	Text curManaEnemy("", font, 25);
	Text maxManaEnemy("", font, 25);
	Text handEnemy("", font, 25);
	Text deckEnemy("", font, 25);
	Text hpPlayer("", font, 30);
	Text curManaPlayer("", font, 25);
	Text maxManaPlayer("", font, 25);
	Text handPlayer("", font, 25);
	Text deckPlayer("", font, 25);
	hpEnemy.setColor(Color::Red);
	curManaEnemy.setColor(Color::Cyan);
	maxManaEnemy.setColor(Color::Blue);
	handEnemy.setColor(Color::Green);
	deckEnemy.setColor(Color::Yellow);
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
	sf::String allNames[ALL_CARDS] = {
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
	MinionCard allCards[ALL_CARDS];
	Picture picBuff = Picture(allNames[0], 0, 0, 286, 395);
	MinionCard minionBuff = MinionCard(picBuff, "Bloodfen Raptor", 3, 2, 2, false);
	allCards[0] = minionBuff;
	picBuff = Picture(allNames[1], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Booty Bay Bodyguard", 5, 4, 5, true);
	allCards[1] = minionBuff;
	picBuff = Picture(allNames[2], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Boulderfist Ogre", 6, 7, 6, false);
	allCards[2] = minionBuff;
	picBuff = Picture(allNames[3], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Chillwind Yeti", 4, 5, 4, false);
	allCards[3] = minionBuff;
	picBuff = Picture(allNames[4], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Core Hound", 9, 5, 7, false);
	allCards[4] = minionBuff;
	picBuff = Picture(allNames[5], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Frostwolf Grunt", 2, 2, 2, true);
	allCards[5] = minionBuff;
	picBuff = Picture(allNames[6], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Goldshire Footman", 1, 2, 1, true);
	allCards[6] = minionBuff;
	picBuff = Picture(allNames[7], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Ironfur Grizzly", 3, 3, 3, true);
	allCards[7] = minionBuff;
	picBuff = Picture(allNames[8], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Lord of the Arena", 6, 5, 6, true);
	allCards[8] = minionBuff;
	picBuff = Picture(allNames[9], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Magma Rager", 5, 1, 3, false);
	allCards[9] = minionBuff;
	picBuff = Picture(allNames[10], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Murloc Raider", 2, 1, 1, false);
	allCards[10] = minionBuff;
	picBuff = Picture(allNames[11], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Oasis Snapjaw", 2, 7, 4, false);
	allCards[11] = minionBuff;
	picBuff = Picture(allNames[12], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "River Crocolisk", 2, 3, 2, false);
	allCards[12] = minionBuff;
	picBuff = Picture(allNames[13], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Sen'jin Shieldmasta", 3, 5, 4, true);
	allCards[13] = minionBuff;
	picBuff = Picture(allNames[14], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "Silverback Patriarch", 1, 4, 3, true);
	allCards[14] = minionBuff;
	picBuff = Picture(allNames[15], 0, 0, 286, 395);
	minionBuff = MinionCard(picBuff, "War Golem", 7, 7, 7, false);
	allCards[15] = minionBuff;

	Player human = Player();
	Player comp = Player();
	human.deck.prepare(allCards);
	comp.deck.prepare(allCards);
	//===============DECK_INIT_END


	while (window.isOpen()) { //MAIN CYCLE OF SFML
		float time = clock.getElapsedTime().asMicroseconds(); //receiving passed time (in ms)
		clock.restart(); //restarting clock
						 //std::cout << time << "\n"; //showing the time passed in console

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) // if "close" button is clicked - close window
				window.close();
		}
		window.clear(); // clear all the window

						// draw the map
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == 'h') {
					map.sprite.setTextureRect(IntRect(96, 0, 32, 32));
				}
				else if (TileMap[i][j] == 'c') {
					map.sprite.setTextureRect(IntRect(64, 0, 32, 32));
				}
				else if ((TileMap[i][j] == 'b')) {
					map.sprite.setTextureRect(IntRect(0, 0, 32, 32));
				}
				else if ((TileMap[i][j] == ' ')) {
					map.sprite.setTextureRect(IntRect(32, 0, 32, 32));
				}
				map.sprite.setPosition(j * 32, i * 32);
				window.draw(map.sprite);
			}
		}

		// draw cards (enemy bf, human bf, human hand)
		for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
			comp.bf.cardList[i].pic.sprite.setPosition(192 * i, 160);
			window.draw(comp.bf.cardList[i].pic.sprite);
		}
		for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
			human.bf.cardList[i].pic.sprite.setPosition(192 * i, 320);
			window.draw(human.bf.cardList[i].pic.sprite);
		}
		for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
			human.hand.cardList[i].pic.sprite.setPosition(128 * (i + 1), 480);
			window.draw(human.hand.cardList[i].pic.sprite);
		}

		// draw text: hp/mana/cards
		ostringstream buff;
		// enemy
		buff.str("");
		buff << "30";
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
		buff << "30";
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
		human.startTurn();
		comp.startTurn();
		char a;
		do {
			a = getch();
			printf("%c", a);
		} while (a != 'k');
		human.playCard(0);
		comp.playCard(0);
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