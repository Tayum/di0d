/*
=====HERO CLASS (raw)=====
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