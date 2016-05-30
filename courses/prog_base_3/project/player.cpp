#include "player.h"

Player::Player(std::string heroName, Picture * heroPic)
	: deck(), hand(), bf(), hero(heroName, heroPic) {
	//deck = Deck();
	//hand = Hand();
	//bf = Battlefield();
	turn = Turn();
}
Player::Player(Deck deck, Hand hand, Battlefield battlefield, Hero hero) : hero(hero) {
	this->deck = deck;
	this->hand = hand;
	this->bf = battlefield;
	//this->hero = hero;
	turn = Turn();
}

void Player::drawCard() {
	MinionCard card = deck.popLast();
	if (card.getCurHealth() != 0) {
		hand.addLast(card);
	}
}

void Player::playCard(int indexHand) {
	if (!bf.isFull() && hand.isValidInd(indexHand) && hand.mana.isEnough(hand.cardList[indexHand])) {
		MinionCard card = hand.delByInd(indexHand);
		hand.mana.useCard(card);
		bf.addLast(card);
	}
}

void Player::startTurn() {
	turn.start();
	hand.mana.onTurnStart();
	for (int i = 0; i < bf.getCurCardAmount(); i++) {
		bf.cardList[i].setHasAttacked(false);
	}
	hero.setHasUsedHeroPower(false);
	drawCard();
}

void Player::endTurn() {
	turn.end();
}