#include <vector>

#include "SFML/Audio.hpp"
#include "picture.h"

#include "menu.h"

using namespace sf;

typedef enum {
	NOMENU,
	NEWGAME,
	ABOUT,
	EXIT
} menuButton;

void mainMenu(RenderWindow * window) {
	Picture mainMenu = Picture("mainMenu.png", 0, 0, 1366, 768);
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
		menuButtonNum = NOMENU;
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

typedef enum {
	NOCLICK,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	REPICK
} cardRepick;

bool * repickMenu(RenderWindow * window, Player * human, int isFirst) {
	bool * isRepicked = new  bool[4];
	for (int i = 0; i < 4; i++) {
		isRepicked[i] = false;
	}
	MinionCard cardsToRepick[4];

	Picture repickMenu = Picture("repickMenu.png", 0, 0, 1366, 768);
	Picture startingHand = Picture("startingHand.png", 0, 0, 286, 100);
	Picture repickButton = Picture("repick.png", 0, 0, 150, 50);
	startingHand.sprite.setPosition(540, 0);
	repickButton.sprite.setPosition(608, 641.5);
	for (int i = 0; i < 4; i++) {
		cardsToRepick[i] = human->deck.getByInd(29 - i);
	}
	for (int i = 0; i < 4 - isFirst; i++) {
		cardsToRepick[i].pic->sprite.setPosition((286 + 74) * i + 180 * isFirst, 186.5);
	}


	Music music;
	music.openFromFile("music/collectionManager.ogg");
	music.play();


	cardRepick cardRepickNum;
	Vector2i mousePos;
	bool isMenuOpened = true;
	Clock clock;
	float clickTimer = 0;
	while (isMenuOpened) {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		clickTimer += time;
		for (int i = 0; i < 4 - isFirst; i++) {
			if (isRepicked[i]) {
				cardsToRepick[i].pic->sprite.setColor(Color::Red);
			}
			else {
				cardsToRepick[i].pic->sprite.setColor(Color::White);
			}
		}

		cardRepickNum = NOCLICK;
		mousePos = Mouse::getPosition((*window));
		window->clear();

		for (int i = 0; i < 4 - isFirst; i++) {
			if (repickButton.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				cardRepickNum = REPICK;
			}
			else if (cardsToRepick[i].pic->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				cardsToRepick[i].pic->sprite.setColor(Color::Green);
				cardRepickNum = (cardRepick)(1 + i);
				break;
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (cardRepickNum == REPICK) {
				for (int i = 0; i < 4 - isFirst; i++) {
					cardsToRepick[i].pic->sprite.setColor(Color::White);
				}
				music.stop();
				return isRepicked;
			}
			if (clickTimer >= 250) {
				for (int i = 0; i < 4 - isFirst; i++) {
					if (cardRepickNum == 1 + i) {
						isRepicked[i] = !isRepicked[i];
						clickTimer = 0;
						break;
					}
				}
			}
		}

		window->draw(repickMenu.sprite);
		for (int i = 0; i < 4 - isFirst; i++) {
			window->draw(cardsToRepick[i].pic->sprite);
		}
		window->draw(startingHand.sprite);
		window->draw(repickButton.sprite);
		window->display();
	}
}

void endMenu(Player * human, Player * computer, sf::RenderWindow * window) {
	Music music;
	music.openFromFile("music/end.ogg");
	music.play();

	// Victory
	if (human->hero.getCurHP() >= 0 && computer->hero.getCurHP() <= 0) {
		Picture background = Picture("victoryBackground.png", 0, 0, 1366, 768);
		Picture foreground = Picture("victory.png", 0, 0, 700, 576);
		foreground.sprite.setScale(0.686, 0.686);
		foreground.sprite.setPosition(433, 186.5);
		do {
			window->draw(background.sprite);
			window->draw(foreground.sprite);
			window->display();
		} while (!Keyboard::isKeyPressed(Keyboard::Escape));
	}
	// Defeat / "Concede" button was pressed
	else if ((computer->hero.getCurHP() >= 0 && human->hero.getCurHP() <= 0) || (human->hero.getCurHP() > 0 && computer->hero.getCurHP() > 0)) {
		Picture background = Picture("defeatBackground.png", 0, 0, 1366, 768);
		Picture foreground = Picture("defeat.png", 0, 0, 576, 639);
		foreground.sprite.setScale(0.618, 0.618);
		foreground.sprite.setPosition(495, 186.5);
		do {
			window->draw(background.sprite);
			window->draw(foreground.sprite);
			window->display();
		} while (!Keyboard::isKeyPressed(Keyboard::Escape));
	}

	music.stop();
	window->close();
}