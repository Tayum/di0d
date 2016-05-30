#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "deck.h"
#include "hand.h"
#include "battlefield.h"
#include "turn.h"
#include "hero.h"

class Player {
public:
	Deck deck;
	Hand hand;	// Mana class is inside
	Battlefield bf;
	Turn turn;
	Hero hero;

	Player(std::string heroName, Picture * heroPic);
	Player(Deck deck, Hand hand, Battlefield battlefield, Hero hero);

	void drawCard();
	void playCard(int indexHand);
	void startTurn();
	void endTurn();

};

#endif // PLAYER_H_INCLUDED