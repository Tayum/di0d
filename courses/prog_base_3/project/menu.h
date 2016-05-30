#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "player.h"

void mainMenu(sf::RenderWindow * window);
bool * repickMenu(sf::RenderWindow * window, Player * human, int isFirst);

#endif // MENU_H_INCLUDED
