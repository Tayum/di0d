#include <vector>

#include "menu.h"
#include "picture.h"

#include "SFML/Audio.hpp"

using namespace sf;

typedef enum {
	NOTHING,
	NEWGAME,
	ABOUT,
	EXIT
} menuButton;

void menu(RenderWindow * window) {
	Picture mainMenu = Picture("menu.png", 0, 0, 1366, 768);
	Picture newGame = Picture("newGame.png", 0, 0, 150, 30);
	Picture about = Picture("about.png", 0, 0, 85, 30);
	Picture exit = Picture("exit.png", 0, 0, 60, 30);
	Picture aboutPic = Picture("aboutPic.png", 0, 0, 1366, 768);

	newGame.sprite.setPosition(630, 252.5);
	about.sprite.setPosition(662.5, 325.5);
	exit.sprite.setPosition(668.5, 401.5);

	bool isMenuOpened = true;
	menuButton menuButtonNum;
	Vector2i mousePos;

	Music music;
	music.openFromFile("music/mainMenu.ogg");
	music.play();
	music.setLoop(true);

	while (isMenuOpened) {
		newGame.sprite.setColor(Color::White);
		about.sprite.setColor(Color::White);
		exit.sprite.setColor(Color::White);
		menuButtonNum = NOTHING;
		mousePos = Mouse::getPosition((*window));
		window->clear();

		if (newGame.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			newGame.sprite.setColor(Color::Yellow);
			menuButtonNum = NEWGAME;
		}
		if (about.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			about.sprite.setColor(Color::Yellow);
			menuButtonNum = ABOUT;
		}
		if (exit.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			exit.sprite.setColor(Color::Yellow);
			menuButtonNum = EXIT;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuButtonNum == NEWGAME) {
				isMenuOpened = false;
				music.stop();
			}
			if (menuButtonNum == ABOUT) {
				do {
					window->draw(aboutPic.sprite);
					window->display();
				} while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuButtonNum == EXIT) {
				isMenuOpened = false;
				music.stop();
				window->close();
			}
		}

		window->draw(mainMenu.sprite);
		window->draw(newGame.sprite);
		window->draw(about.sprite);
		window->draw(exit.sprite);
		
		window->display();
	}
}