#include <SFML/Audio.hpp>
#include "menu.h"

#include "general.h"

using namespace sf;

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

void startGame(Player * human, Player * computer, RenderWindow * window) {
	int isHumanFirst = rand() % 2;
	computer->deck.repickComp(1 - isHumanFirst);
	human->deck.repickPlayer(repickMenu(window, human, isHumanFirst), isHumanFirst);
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