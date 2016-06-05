#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "player.h"

void mainMenu(sf::RenderWindow * window);
bool * repickMenu(sf::RenderWindow * window, Player * human, int isFirst);
void endMenu(Player * human, Player * computer, sf::RenderWindow * window);

#endif // MENU_H_INCLUDED
