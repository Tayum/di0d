#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include "player.h"
#include <SFML/Graphics.hpp>

void attack(Player * human, Player * computer, int cardAttackerInd, int cardDefenderInd);
void attack(Player * human, Player * computer, int cardAttackerInd);
void useHeroPower(Player * human, Player * computer);
void useHeroPower(Player * human, Player * computer, int cardDefenderInd);
void endTurn(Player * human, Player * computer);
void startGame(Player * human, Player * computer, sf::RenderWindow * window);

#endif // GENERAL_H_INCLUDED