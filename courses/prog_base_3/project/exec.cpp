#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

#include <SFML/Audio.hpp>

#include "exec.h"
#include "player.h"
#include "background.h"
#include "menu.h"
#include "general.h"

using namespace std;
using namespace sf;

typedef enum {
	HAND = 1,
	BF,
	HERO,
	HERO_POWER
} clickType;

void initDeck(MinionCard * allCards);
void bgDraw(RenderWindow * window, Picture * background);
void AI_Easy(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton);
void AI_Hard(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton);


void exec(log_cb_ptr log_cb_func) {
	Clock clock;
	clock.restart();
	Picture background = Picture("backgroundTilesets.png", 0, 0, 128, 32);
	
	//===============FONT
	Font font;
	font.loadFromFile("font/CyrilicOld.TTF");
	Text heroNameEnemy("", font, 20);
	Text hpEnemy("", font, 30);
	Text curManaEnemy("", font, 25);
	Text handEnemy("", font, 25);
	Text deckEnemy("", font, 25);
	Text heroNamePlayer("", font, 25);
	Text hpPlayer("", font, 30);
	Text curManaPlayer("", font, 25);
	Text handPlayer("", font, 25);
	Text deckPlayer("", font, 25);
	Text bfTextPlayer[7];
	for (int i = 0; i < 7; i++) {
		bfTextPlayer[i] = Text("", font, 22);
		bfTextPlayer[i].setString("ATTACK");
	}
	Text bfHPTextPlayer[7];
	Text bfHPTextEnemy[7];
	for (int i = 0; i < 7; i++) {
		bfHPTextPlayer[i] = Text("", font, 29);
		bfHPTextPlayer[i].setStyle(Text::Bold);
		bfHPTextEnemy[i] = Text("", font, 29);
		bfHPTextEnemy[i].setStyle(Text::Bold);
	}

	heroNameEnemy.setColor(Color::White);
	hpEnemy.setColor(Color::Red);
	curManaEnemy.setColor(Color::Blue);
	handEnemy.setColor(Color::Green);
	deckEnemy.setColor(Color::Yellow);
	heroNamePlayer.setColor(Color::White);
	hpPlayer.setColor(Color::Red);
	curManaPlayer.setColor(Color::Blue);
	handPlayer.setColor(Color::Green);
	deckPlayer.setColor(Color::Yellow);
	hpEnemy.setStyle(Text::Bold);
	curManaEnemy.setStyle(Text::Bold);
	handEnemy.setStyle(Text::Italic);
	deckEnemy.setStyle(Text::Bold);
	hpPlayer.setStyle(Text::Bold);
	curManaPlayer.setStyle(Text::Bold);
	handPlayer.setStyle(Text::Italic);
	deckPlayer.setStyle(Text::Bold);
	//===============FONT_END

	//===============CALLBACK
	std::ostringstream strBuf;
	strBuf.str("");
	strBuf << "Loaded font: " << clock.restart().asMilliseconds() << " millisec taken;\n\n";
	log_cb_func(&strBuf);
	//===============CALLBACK_END

	MinionCard allCards[ALL_CARDS];
	initDeck(allCards);

	//===============CALLBACK
	strBuf.str("");
	strBuf << "Deck initialized: " << clock.restart().asMilliseconds() << " millisec taken;\n\n";
	log_cb_func(&strBuf);
	//===============CALLBACK_END

	//===============HERO POWER
	Picture fireblast = Picture("fireblast.png", 0, 0, 286, 395);
	fireblast.sprite.setScale(0.447, 0.405);
	fireblast.sprite.setPosition(1056, 0);
	//===============HERO POWER_END

	//===============CONCEDE BUTTON
	Picture concedeButton = Picture("concede.png", 0, 0, 160, 160);
	concedeButton.sprite.setPosition(160, 0);
	//===============CONCEDE BUTTON_END

	//===============BF HEART
	Picture bfHeart = Picture("heart.png", 0, 0, 65, 95);
	bfHeart.sprite.setScale(0.475, 0.442);
	//===============BF HEART_END

	//===============TEXT INFO
	Picture textPic = Picture("text.png", 0, 0, 200, 90);
	Vector2i mouseMovePos;
	Text infoText("", font, 20);
	infoText.setStyle(sf::Text::Style::Italic);
	bool isText = false;
	//===============TEXT INFO_END

	//===============PLAYER_INIT
	Picture picBuffHuman = Picture("jaina.png", 0, 0, 200, 200);
	Player human = Player("Jaina", &picBuffHuman);
	human.hero.pic->sprite.setScale(0.48, 0.48);
	Picture picBuffComp = Picture("guldan.png", 0, 0, 200, 200);
	Player comp = Player("Gul'dan", &picBuffComp);
	comp.hero.pic->sprite.setScale(0.48, 0.48);
	//===============CALLBACK
	strBuf.str("");
	strBuf << "Players created: " << clock.restart().asMilliseconds() << " millisec taken;\n\n";
	log_cb_func(&strBuf);
	//===============CALLBACK_END
	// Deck prep for players
	human.deck.prepare(allCards);
	comp.deck.prepare(allCards);
	//===============PLAYER_INIT_END

	//===============CALLBACK
	strBuf.str("");
	strBuf << "Players' decks prepared: " << clock.restart().asMilliseconds() << " millisec taken;\n\n";
	log_cb_func(&strBuf);
	//===============CALLBACK_END

	//===============MOUSE CONTROL
	bool isClicked = false;
	clickType type = HAND;
	int indFirstClick = 0;
	Vector2i mouseClickPos;
	//===============MOUSE CONTROL_END

	RenderWindow window(sf::VideoMode(1366, 768), "Candlehearth", sf::Style::Fullscreen); //, sf::Style::Fullscreen

	//===============MAIN MENU
	bool difficulty = mainMenu(&window);
	//===============MAIN MENU_END

	// If "exit" button was pressed:
	if (window.isOpen() == false) {
		return;
	}

	//===============START GAME (+ cards repick menu)
	startGame(&human, &comp, &window);
	//===============START GAME_END

	//===============END TURN BUTTON
	Picture endTurnButton = Picture("endTurn.png", 0, 0, 320, 160);
	if (human.turn.isTurn()) {
		endTurnButton.sprite.setTextureRect(IntRect(0, 0, 160, 160));
	}
	else {
		endTurnButton.sprite.setTextureRect(IntRect(160, 0, 160, 160));
	}
	endTurnButton.sprite.setPosition(1184, 0);
	//===============END TURN BUTTON_END

	//===============MUSIC
	Music music;
	music.openFromFile("music/tabletopBattles.ogg");
	music.play();
	music.setLoop(true);
	//===============MUSIC_END

	//===============TIMER
	float enemyTurnTimer = 0;
	clock.restart();
	//===============TIMER_END

	while (window.isOpen()) { // Main cycle

		// Check on end of game
		if (human.hero.getCurHP() <= 0 || comp.hero.getCurHP() <= 0) {
			music.stop();
			endMenu(&human, &comp, &window);
			break;
		}

		float time = clock.restart().asMilliseconds();
		enemyTurnTimer += time;


		// Showing info
		isText = false;
		mouseMovePos = Mouse::getPosition(window);
		std::ostringstream infoBuff;
		infoBuff.str("");
		// Enemy
		if (hpEnemy.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(hpEnemy.getPosition().x, hpEnemy.getPosition().y + 35);
			infoBuff << "Current HP of your\nenemy.\nOnce it reaches zero,\nyou will win!";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(hpEnemy.getPosition().x, hpEnemy.getPosition().y + 35);
			isText = true;
		}
		else if (handEnemy.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(handEnemy.getPosition().x, handEnemy.getPosition().y + 35);
			infoBuff << "Current amount of\ncards in hand of\nyour enemy. Maximum\nof 10 cards at once.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(handEnemy.getPosition().x, handEnemy.getPosition().y + 35);
			isText = true;
		} 
		else if (comp.hero.pic->sprite.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(comp.hero.pic->sprite.getPosition().x, comp.hero.pic->sprite.getPosition().y + 100);
			infoBuff << "Your enemy, Warlock\nGul'Dan.\nHit him in the face\nto deal damage!";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(comp.hero.pic->sprite.getPosition().x, comp.hero.pic->sprite.getPosition().y + 100);
			isText = true;
		}
		else if (curManaEnemy.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(curManaEnemy.getPosition().x, curManaEnemy.getPosition().y + 35);
			infoBuff << "Cur.mana/Max.mana of\nyour enemy. Refills /\ngrows up to 10 at the\nstart of enemy turn.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(curManaEnemy.getPosition().x, curManaEnemy.getPosition().y + 35);
			isText = true;
		}
		else if (deckEnemy.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(deckEnemy.getPosition().x, deckEnemy.getPosition().y + 35);
			infoBuff << "Current amount of\ncards in deck of your\nenemy. Deck contains\n30 cards at the start.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(deckEnemy.getPosition().x, deckEnemy.getPosition().y + 35);
			isText = true;
		}
		// Player
		else if (hpPlayer.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(hpPlayer.getPosition().x, hpPlayer.getPosition().y - 95);
			infoBuff << "Your current HP.\nOnce it reaches zero,\nyou will lose!";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(hpPlayer.getPosition().x, hpPlayer.getPosition().y - 95);
			isText = true;
		}
		else if (handPlayer.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(handPlayer.getPosition().x, handPlayer.getPosition().y - 95);
			infoBuff << "Current amount of\ncards in your hand.\nMaximum of 10 cards\nat once.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(handPlayer.getPosition().x, handPlayer.getPosition().y - 95);
			isText = true;
		}
		else if (human.hero.pic->sprite.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(human.hero.pic->sprite.getPosition().x, human.hero.pic->sprite.getPosition().y - 95);
			infoBuff << "You, Mage Jaina\nProudmoore. Try to\ndefeat your enemy!";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(human.hero.pic->sprite.getPosition().x, human.hero.pic->sprite.getPosition().y - 95);
			isText = true;
		}
		else if (curManaPlayer.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(curManaPlayer.getPosition().x, curManaPlayer.getPosition().y - 95);
			infoBuff << "Your Cur. mana / Max.\nmana. Refills / grows\nup to 10 at the\nstart of your turn.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(curManaPlayer.getPosition().x, curManaPlayer.getPosition().y - 95);
			isText = true;
		}
		else if (deckPlayer.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(deckPlayer.getPosition().x, deckPlayer.getPosition().y - 95);
			infoBuff << "Current amount of\ncards in your deck.\nDeck contains 30\ncards at the start.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(deckPlayer.getPosition().x, deckPlayer.getPosition().y - 95);
			isText = true;
		}
		// Buttons
		else if (concedeButton.sprite.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(concedeButton.sprite.getPosition().x, concedeButton.sprite.getPosition().y + 165);
			infoBuff << "Concede button. Press\nit to concede (thnx,\nSherlock!) and end the\ngame immideately.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(concedeButton.sprite.getPosition().x, concedeButton.sprite.getPosition().y + 165);
			isText = true;
		}
		else if (fireblast.sprite.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(fireblast.sprite.getPosition().x, fireblast.sprite.getPosition().y + 165);
			infoBuff << "Hero power.Deals 1 dmg\nto the chosen enemy.\nMay be used once a\nturn. Costs 2 mana.";
			infoText.setString("" + infoBuff.str());
			infoText.setPosition(fireblast.sprite.getPosition().x, fireblast.sprite.getPosition().y + 165);
			isText = true;
		}
		else if (endTurnButton.sprite.getGlobalBounds().contains(mouseMovePos.x, mouseMovePos.y)) {
			textPic.sprite.setPosition(endTurnButton.sprite.getPosition().x - 32, endTurnButton.sprite.getPosition().y + 165);
			if (endTurnButton.sprite.getTextureRect() == IntRect(0, 0, 160, 160)) {
				infoBuff << "End turn button.\nPress it to end the\nturn.\n(Captain Obvious!)";
				infoText.setString("" + infoBuff.str());
			}
			else if (endTurnButton.sprite.getTextureRect() == IntRect(160, 0, 160, 160)) {
				infoBuff << "The enemy turn is in\nprocess. Wait for\nenemy to end the turn.";
				infoText.setString("" + infoBuff.str());
			}
			infoText.setPosition(endTurnButton.sprite.getPosition().x - 32, endTurnButton.sprite.getPosition().y + 165);
			isText = true;
		}


		// Events
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { // "Close" button
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && human.turn.isTurn()) {
				if (event.key.code == Mouse::Left) { // (LMB)
					mouseClickPos = Mouse::getPosition(window);

					// CONCEDE BUTTON CLICK
					if (concedeButton.sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
						music.stop();
						endMenu(&human, &comp, &window);
						break;
					}

					// END TURN BUTTON CLICK
					if (endTurnButton.sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {

						for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
							human.hand.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
							human.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < comp.bf.getCurCardAmount();  i++) {
							comp.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						fireblast.sprite.setColor(Color::White);
						// Switch to "Enemy turn" button
						endTurnButton.sprite.setTextureRect(IntRect(160, 0, 160, 160));

						isClicked = false;
						endTurn(&human, &comp);

						// Nullifying the timer for enemy to wait another 1 second at the start of the turn
						clock.restart();
						enemyTurnTimer = 0;
					}

					// IF THE BUTTON WAS NOT CLICKED BEFORE!
					if (!isClicked) {
						// CLICK FOR HERO POWER!
						if (human.hero.hasUsedHeroPower() == false && human.hand.mana.isEnough(2) && fireblast.sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
							type = HERO_POWER;
							isClicked = true;
							fireblast.sprite.setColor(Color::Green);
						}
						else {
							// CLICK FOR HAND (PLAYER)!
							if (!isClicked) {
								for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
									if (human.hand.mana.isEnough(human.hand.cardList[i]) && human.hand.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
										indFirstClick = i;
										type = HAND;
										isClicked = true;
										human.hand.cardList[i].pic->sprite.setColor(Color::Green);
										break;
									}
								}
							}
							if (!isClicked) {
								// CLICK FOR BATTLEFIELD (PLAYER)!
								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									if (human.bf.cardList[i].hasAttacked() == false && human.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
										indFirstClick = i;
										type = BF;
										isClicked = true;
										human.bf.cardList[i].pic->sprite.setColor(Color::Green);

										for (int j = 0; j < comp.bf.getCurCardAmount(); j++) {
											if (comp.bf.cardList[j].getTaunt()) {
												comp.bf.cardList[j].pic->sprite.setColor(Color::Red);
											}
										}

										break;
									}
								}
							}
						}

					}

					// IF THE BUTTON WAS CLICKED BEFORE!
					if (isClicked) {
						if (type == HAND) {
							// CLICK FOR BF (PLAYER)!
							if (IntRect(0, 160, 1366, 440).contains(mouseClickPos.x, mouseClickPos.y)) {
								human.playCard(indFirstClick);
								isClicked = false;

								for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
									human.hand.cardList[i].pic->sprite.setColor(Color::White);
								}
								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									human.bf.cardList[i].pic->sprite.setColor(Color::White);
								}

								break;
							}
						}

						else if (type == HERO_POWER) {
							// CLICK FOR BF (ENEMY)!
							for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
								if (comp.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
									useHeroPower(&human, &comp, i);
									isClicked = false;
									fireblast.sprite.setColor(Color::Red);

									break;
								}
							}
							// CLICK FOR HERO (ENEMY)!
							if (comp.hero.pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
								useHeroPower(&human, &comp);

								fireblast.sprite.setColor(Color::Red);

								isClicked = false;
							}
						}

						else if (type == BF) {
							// CLICK FOR BF (ENEMY)!
							for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
								if (comp.bf.cardList[i].pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
									attack(&human, &comp, indFirstClick, i);

									for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
										human.bf.cardList[i].pic->sprite.setColor(Color::White);
									}


									for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
										comp.bf.cardList[i].pic->sprite.setColor(Color::White);
									}

									isClicked = false;
									break;
								}
							}
							// CLICK FOR HERO (ENEMY)!
							if (comp.hero.pic->sprite.getGlobalBounds().contains(mouseClickPos.x, mouseClickPos.y)) {
								attack(&human, &comp, indFirstClick);

								for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
									human.bf.cardList[i].pic->sprite.setColor(Color::White);
								}

								for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
									comp.bf.cardList[i].pic->sprite.setColor(Color::White);
								}

								isClicked = false;
							}
						}

					}

				}

				if (event.key.code == Mouse::Right) { // (RMB)
					if (isClicked) {

						for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
							human.hand.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
							human.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
							comp.bf.cardList[i].pic->sprite.setColor(Color::White);
						}
						if (fireblast.sprite.getColor() == Color::Green) {
							fireblast.sprite.setColor(Color::White);
						}

						isClicked = false;
					}
				}

			}

		}

		// Difficulty choice: TRUE - Hard, FALSE - Easy
		if (difficulty == false) {
			AI_Easy(&human, &comp, &enemyTurnTimer, &endTurnButton);
		}
		else if (difficulty) {
			AI_Hard(&human, &comp, &enemyTurnTimer, &endTurnButton);
		}

		window.clear(); // Clear the window

		bgDraw(&window, &background);

		// Draw: Cards (enemy BF, human BF (+ attack state, BF hearts, curHP), human Hand)
		std::ostringstream buff;
		std::ostringstream buffMana;
		for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
			comp.bf.cardList[i].pic->sprite.setPosition(192 * i, 160);
			window.draw(comp.bf.cardList[i].pic->sprite);

			bfHeart.sprite.setPosition(192 * i + 149, 341);
			window.draw(bfHeart.sprite);

			buff.str("");
			buff << comp.bf.cardList[i].getCurHealth();
			bfHPTextEnemy[i].setString("" + buff.str());
			bfHPTextEnemy[i].setPosition(192 * i + 158, 344);
			window.draw(bfHPTextEnemy[i]);
		}
		for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
			human.bf.cardList[i].pic->sprite.setPosition(192 * i, 384);
			window.draw(human.bf.cardList[i].pic->sprite);

			if (human.bf.cardList[i].hasAttacked() == false) {
				bfTextPlayer[i].setColor(Color::Green);
			}
			else {
				bfTextPlayer[i].setColor(Color::Red);
			}
			bfTextPlayer[i].setPosition(192 * i + 52, 576);
			window.draw(bfTextPlayer[i]);

			bfHeart.sprite.setPosition(192 * i + 149, 565);
			window.draw(bfHeart.sprite);

			buff.str("");
			buff << human.bf.cardList[i].getCurHealth();
			bfHPTextPlayer[i].setString("" + buff.str());
			bfHPTextPlayer[i].setPosition(192 * i + 158, 568);
			window.draw(bfHPTextPlayer[i]);
		}
		for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
			human.hand.cardList[i].pic->sprite.setPosition(128 * (i + 1), 600);
			window.draw(human.hand.cardList[i].pic->sprite);
		}

		// Draw: "End turn" button
		window.draw(endTurnButton.sprite);
		// Draw: Hero power
		window.draw(fireblast.sprite);
		// Draw: "Concede" button
		window.draw(concedeButton.sprite);

		// Draw: Hero (portrait, name)
		// enemy
		comp.hero.pic->sprite.setPosition(32, 32);
		window.draw(comp.hero.pic->sprite);

		buff.str("");
		buff << comp.hero.getName();
		heroNameEnemy.setString("" + buff.str());
		heroNameEnemy.setPosition(32, 0);
		window.draw(heroNameEnemy);
		// human
		human.hero.pic->sprite.setPosition(32, 640);
		window.draw(human.hero.pic->sprite);

		buff.str("");
		buff << human.hero.getName();
		heroNamePlayer.setString("" + buff.str());
		heroNamePlayer.setPosition(32, 608);
		window.draw(heroNamePlayer);

		// Draw: info about player
		// enemy
		buff.str("");
		buff << comp.hero.getCurHP();
		hpEnemy.setString("" + buff.str());
		hpEnemy.setPosition(0, 0);

		buff.str("");
		buff << comp.hand.mana.getCurMana();
		buffMana.str("");
		buffMana << comp.hand.mana.getCurMaxMana();
		curManaEnemy.setString("" + buff.str() + "/" + buffMana.str());
		curManaEnemy.setPosition(0, 128);

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
		buff << human.hero.getCurHP();
		hpPlayer.setString("" + buff.str());
		hpPlayer.setPosition(0, 608);

		buff.str("");
		buff << human.hand.mana.getCurMana();
		buffMana.str("");
		buffMana << human.hand.mana.getCurMaxMana();
		curManaPlayer.setString("" + buff.str() + "/" + buffMana.str());
		curManaPlayer.setPosition(0, 736);

		buff.str("");
		buff << human.hand.getCurCardAmount();
		handPlayer.setString("" + buff.str());
		handPlayer.setPosition(96, 608);

		buff.str("");
		buff << human.deck.getCurCardAmount();
		deckPlayer.setString("" + buff.str());
		deckPlayer.setPosition(96, 736);

		window.draw(hpEnemy);
		window.draw(curManaEnemy);
		window.draw(handEnemy);
		window.draw(deckEnemy);
		window.draw(hpPlayer);
		window.draw(curManaPlayer);
		window.draw(handPlayer);
		window.draw(deckPlayer);
		if (isText) {
			window.draw(textPic.sprite);
			window.draw(infoText);
		}
		window.display(); // Display the window's draws

	}

}

//===============DECK_INIT
void initDeck(MinionCard * allCards) {

	std::string allNames[] = {
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
	std::string allCardNames[] = {
		"Bloodfen Raptor",
		"Booty Bay Bodyguard",
		"Boulderfist Ogre",
		"Chillwind Yeti",
		"Core Hound",
		"Frostwolf Grunt",
		"Goldshire Footman",
		"Ironfur Grizzly",
		"Lord of the Arena",
		"Magma Rager",
		"Murloc Raider",
		"Oasis Snapjaw",
		"River Crocolisk",
		"Sen'jin Shieldmasta",
		"Silverback Patriarch",
		"War Golem"
	};
	int allAttack[] = { 3,5,6,4,9,2,1,3,6,5,2,2,2,3,1,7 };
	int allHP[] = { 2,4,7,5,5,2,2,3,5,1,1,7,3,5,4,7 };
	int allManacost[]{ 2,5,6,4,7,2,1,3,6,3,1,4,2,4,3,7 };
	bool allTaunt[] = { false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,false };


	std::list<Picture *>  picList;
	std::list<Picture *>::iterator iterList;
	for (int i = 0; i < ALL_CARDS; i++) {
		picList.push_back(new Picture(allNames[i], 0, 0, 286, 395));
	}
	MinionCard minionBuff;
	int i = 0;
	for (iterList = picList.begin(); iterList != picList.end(); iterList++) {
		minionBuff = MinionCard((*iterList), allCardNames[i], allAttack[i], allHP[i], allManacost[i], allTaunt[i]);
		allCards[i] = minionBuff;
		i++;
	}

}

// Draw background
void bgDraw(RenderWindow * window, Picture * background) {

	for (int i = 0; i < HEIGHT_BG; i++) {
		for (int j = 0; j < WIDTH_BG; j++) {
			if (bgTile[i][j] == 'h') {
				background->sprite.setTextureRect(IntRect(96, 0, 32, 32));
			}
			else if (bgTile[i][j] == 'c') {
				background->sprite.setTextureRect(IntRect(64, 0, 32, 32));
			}
			else if ((bgTile[i][j] == 'b')) {
				background->sprite.setTextureRect(IntRect(0, 0, 32, 32));
			}
			else if ((bgTile[i][j] == ' ')) {
				background->sprite.setTextureRect(IntRect(32, 0, 32, 32));
			}
			background->sprite.setPosition(j * 32, i * 32);
			window->draw(background->sprite);
		}
	}

}

// AI: Easy variant
void AI_Easy(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton) {
	static bool avlAttacks = true;
	static bool avlSummon = true;

	if (comp->turn.isTurn()) {
		if ((*enemyTurnTimer) > 1000) {
			// ATTACK
			if (avlAttacks) {

				for (int i = 0; i <= comp->bf.getCurCardAmount(); i++) {
					if (i == comp->bf.getCurCardAmount()) {
						avlAttacks = false;
						break;
					}
					else if (comp->bf.cardList[i].hasAttacked() == false) {
						if (human->bf.isThereTaunts()) {
							for (int j = 0; j < human->bf.getCurCardAmount(); j++) {
								if (human->bf.cardList[j].getTaunt()) {
									attack(human, comp, i, j);
									break;
								}
							}
						}
						else {
							attack(human, comp, i);
							break;
						}
					}
					else {
						continue;
					}
					break;
				}

			}
			// SUMMON CARDS
			else if (avlSummon) {

				int maxMana = -1;
				int maxManaIndex = -1;
				if (comp->bf.isFull() == false && comp->hand.isEmpty() == false) {
					for (int i = 0; i < comp->hand.getCurCardAmount(); i++) {
						if (comp->hand.mana.isEnough(comp->hand.cardList[i].getManacost()) && comp->hand.cardList[i].getManacost() > maxMana) {
							maxMana = comp->hand.cardList[i].getManacost();
							maxManaIndex = i;
						}
					}
					if (maxMana != -1 && maxManaIndex != -1) {
						comp->playCard(maxManaIndex);
					}
					else {
						avlSummon = false;
					}
				}
				else {
					avlSummon = false;
				}

			}
			// END THE TURN
			if (avlAttacks == false && avlSummon == false) {
				avlAttacks = true;
				avlSummon = true;
				// Switch to "End turn" button
				endTurnButton->sprite.setTextureRect(IntRect(0, 0, 160, 160));

				endTurn(human, comp);
			}

			(*enemyTurnTimer) = 0;

		}

	}

}

// AI: Hard variant
void AI_Hard(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton) {
	bool avlAttacks = false;
	bool avlSummon = false;

	if (comp->turn.isTurn()) {
		if ((*enemyTurnTimer) > 1000) {
			// Available attacks
			for (int i = 0; i < comp->bf.getCurCardAmount(); i++) {
				if (comp->bf.cardList[i].hasAttacked() == false) {
					avlAttacks = true;
					break;
				}
			}
			// Available summons
			if (comp->bf.isFull() == false) {
				for (int i = 0; i < comp->hand.getCurCardAmount(); i++) {
					if (comp->hand.mana.isEnough(comp->hand.cardList[i].getManacost())) {
						avlSummon = true;
						break;
					}
				}
			}

			// Lethals: Player/Comp
			bool isCompLethal = false;
			bool isPlayerLethal = false;
			if (avlAttacks || avlSummon) {
				int curCompAttack = 0;
				int curPlayerHP = 0;
				int curPlayerAttack = 0;
				int curCompHP = 0;
				curCompHP += comp->hero.getCurHP();
				for (int i = 0; i < comp->bf.getCurCardAmount(); i++) {
					if (comp->bf.cardList[i].hasAttacked() == false) {
						curCompAttack += comp->bf.cardList[i].getCurAttack();
					}
					if (comp->bf.cardList[i].getTaunt()) {
						curCompHP += human->bf.cardList[i].getCurHealth();
					}
				}
				curPlayerHP += human->hero.getCurHP();
				for (int i = 0; i < human->bf.getCurCardAmount(); i++) {
					curPlayerAttack += human->bf.cardList[i].getCurAttack();
					if (human->bf.cardList[i].getTaunt()) {
						curPlayerHP += comp->bf.cardList[i].getCurHealth();
					}
				}
				// Hero power
				curPlayerAttack += 1;
				//
				if (curCompAttack >= curPlayerHP) {
					isCompLethal = true;
				}
				if (curPlayerAttack >= curCompHP) {
					isPlayerLethal = true;
				}
			}

			// ====================END THE TURN====================
			if (avlAttacks == false && avlSummon == false) {
				// Switch to "End turn" button
				endTurnButton->sprite.setTextureRect(IntRect(0, 0, 160, 160));

				endTurn(human, comp);
			}

			// ====================SUMMON CARDS====================
			else if (avlSummon) {
				// Most expensive taunt-/non-taunt- card
				int maxMana = -1;
				int maxManaIndex = -1;
				int maxManaTaunt = -1;
				int maxManaTauntIndex = -1;
				for (int i = 0; i < comp->hand.getCurCardAmount(); i++) {
					if (comp->hand.mana.isEnough(comp->hand.cardList[i].getManacost())) {
						if (comp->hand.cardList[i].getTaunt() && comp->hand.cardList[i].getManacost() > maxManaTaunt) {
							maxManaTaunt = comp->hand.cardList[i].getManacost();
							maxManaTauntIndex = i;
						}
						if (comp->hand.cardList[i].getManacost() > maxMana) {
							maxMana = comp->hand.cardList[i].getManacost();
							maxManaIndex = i;
						}
					}
				}
				// If player has lethal - try to summon most expensive taunts
				if (isPlayerLethal) {
					// If there are available taunt-cards to summon
					if (maxManaIndex != -1 && maxManaTaunt != -1) {
						comp->playCard(maxManaTauntIndex);
					}
					// If there are available non-taunt-cards to summon
					else if (maxMana != -1 && maxManaIndex != -1) {
						comp->playCard(maxManaIndex);
					}
				}
				// If player has no lethal - try to summon most expensive cards
				else {
					// If there are available non-taunt-cards to summon
					if (maxMana != -1 && maxManaIndex != -1) {
						comp->playCard(maxManaIndex);
					}
				}

			}

			// ====================ATTACK====================
			else if (avlAttacks) {
				// Initialize info about battlefield to work with
				int compAttacks[7] = { -1,-1,-1,-1,-1,-1,-1 };
				int compHP[7] = { -1,-1,-1,-1,-1,-1,-1 };
				bool compAvlAttacks[7] = { false, false, false, false, false, false, false };
				int humanAttacks[7] = { -1,-1,-1,-1,-1,-1,-1 };
				int humanHP[7] = { -1,-1,-1,-1,-1,-1,-1 };
				bool humanTaunts[7] = { false, false, false, false, false, false, false };
				for (int i = 0; i < comp->bf.getCurCardAmount(); i++) {
					compAttacks[i] = comp->bf.cardList[i].getCurAttack();
					compHP[i] = comp->bf.cardList[i].getCurHealth();
					compAvlAttacks[i] = !(comp->bf.cardList[i].hasAttacked());
				}
				for (int i = 0; i < human->bf.getCurCardAmount(); i++) {
					humanAttacks[i] = human->bf.cardList[i].getCurAttack();
					humanHP[i] = human->bf.cardList[i].getCurHealth();
					humanTaunts[i] = human->bf.cardList[i].getTaunt();
				}

				// If there are taunts on battlefield
				if (human->bf.isThereTaunts()) {
					int targetHP = -1;
					int targetAttack = -1;
					int targetInd = -1;

					// ~~~~~~~~~~~~~~~~~~~~SEPARATION~~~~~~~~~~~~~~~~~~~~
					if (isCompLethal || (isCompLethal == false && isPlayerLethal == false)) {
						// Choosing first taunt target
						for (int i = 0; i < 7; i++) {
							if (humanTaunts[i]) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
								break;
							}
						}
					}
					else if (isPlayerLethal) {
						// Finding target with taunt with biggest attack
						for (int i = 0; i < 7; i++) {
							if (humanTaunts[i] && humanAttacks[i] > targetAttack) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
							}
						}
					}
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					// A card to kill taunt
					int chosenCardAttack = 100;
					int chosenCardInd = -1;
					if (targetHP != -1 && targetAttack != -1 && targetInd != -1) {
						for (int i = 0; i < 7; i++) {
							if (compAvlAttacks[i]) {
								if (compAttacks[i] >= targetHP && compAttacks[i] < chosenCardAttack) {
									chosenCardInd = i;
									chosenCardAttack = compAttacks[i];
								}
							}
						}
					}
					// A card to damage taunt
					if (chosenCardInd == -1) {
						chosenCardAttack = -1;
						for (int i = 0; i < 7; i++) {
							if (compAvlAttacks[i]) {
								if (compAttacks[i] > chosenCardAttack) {
									chosenCardInd = i;
									chosenCardAttack = compAttacks[i];
								}
							}
						}
					}
					if (chosenCardInd != -1) {
						attack(human, comp, chosenCardInd, targetInd);
					}
				}
				// If there are no taunts on battlefield
				else {
					// ~~~~~~~~~~~~~~~~~~~~SEPARATION~~~~~~~~~~~~~~~~~~~~
					if (isCompLethal) {
						// Hit the face
						for (int i = 0; i < 7; i++) {
							if (compAvlAttacks[i]) {
								attack(human, comp, i);
								break;
							}
						}
					}
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					// ~~~~~~~~~~~~~~~~~~~~SEPARATION~~~~~~~~~~~~~~~~~~~~
					else if (isPlayerLethal) {
						// Try to kill/damage non-taunt card with biggest attack
						int targetHP = -1;
						int targetAttack = -1;
						int targetInd = -1;
						// Finding target with biggest attack
						for (int i = 0; i < 7; i++) {
							if (humanAttacks[i] > targetAttack) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
							}
						}
						// A card to kill card with biggest attack
						int chosenCardAttack = 100;
						int chosenCardInd = -1;
						if (targetHP != -1 && targetAttack != -1 && targetInd != -1) {
							for (int i = 0; i < 7; i++) {
								if (compAvlAttacks[i]) {
									if (compAttacks[i] >= targetHP && compAttacks[i] < chosenCardAttack) {
										chosenCardInd = i;
										chosenCardAttack = compAttacks[i];
									}
								}
							}
						}
						// A card to damage card with biggest attack
						if (chosenCardInd == -1) {
							chosenCardAttack = -1;
							for (int i = 0; i < 7; i++) {
								if (compAvlAttacks[i]) {
									if (compAttacks[i] > chosenCardAttack) {
										chosenCardInd = i;
										chosenCardAttack = compAttacks[i];
									}
								}
							}
						}
						if (chosenCardInd != -1) {
							attack(human, comp, chosenCardInd, targetInd);
						}
					}
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					// ~~~~~~~~~~~~~~~~~~~~SEPARATION~~~~~~~~~~~~~~~~~~~~
					else if (isCompLethal == false && isPlayerLethal == false) {
						// Try to kill a card without killing own cards,
						// go to face otherwise
						int targetIndecesArray[7] = { -1,-1,-1,-1,-1,-1,-1 };
						int targetIndecesArraySize = 0;
						int curHumanAttacksInd = 0;
						// Forming the array in order from biggest to smallest attack
						for (int i = 0; i < 7; i++) {
							if (humanAttacks[i] == -1) {
								break;
							}
							else {
								for (int j = 0; j <= targetIndecesArraySize; j++) {
									if (j == targetIndecesArraySize) {
										targetIndecesArray[j] = i;
										targetIndecesArraySize++;
										break;
									}
									else {
										if (humanAttacks[i] == humanAttacks[targetIndecesArray[j]]) {
											if (humanHP[i] > humanHP[targetIndecesArray[j]]) {
												for (int k = targetIndecesArraySize; k > j; k--) {
													targetIndecesArray[k] = targetIndecesArray[k - 1];
												}
												targetIndecesArray[j] = humanAttacks[i];
												targetIndecesArraySize++;
												break;
											}
										}
										else if (humanAttacks[i] > humanAttacks[targetIndecesArray[j]]) {
											for (int k = targetIndecesArraySize; k > j; k--) {
												targetIndecesArray[k] = targetIndecesArray[k - 1];
											}
											targetIndecesArray[j] = humanAttacks[i];
											targetIndecesArraySize++;
											break;
										}
									}
								}
							}
						}
						bool hasAttacked = false;
						// Trying to find a card valid for attacking the targets
						for (int i = 0; i < targetIndecesArraySize; i++) {
							int targetHP = humanHP[i];
							int targetAttack = humanAttacks[i];
							// A card to kill card with biggest attack
							int chosenCardAttack = 100;
							int chosenCardInd = -1;
							for (int i = 0; i < 7; i++) {
								if (compAvlAttacks[i]) {
									if (compAttacks[i] >= targetHP && compHP[i] < targetAttack && compAttacks[i] < chosenCardAttack) {
										chosenCardInd = i;
										chosenCardAttack = compAttacks[i];
									}
								}
							}
							if (chosenCardInd != -1) {
								attack(human, comp, chosenCardInd, i);
								hasAttacked = true;
								break;
							}
						}
						// If there are valid cards to attack the targets
						if (hasAttacked == false) {
							for (int i = 0; i < 7; i++) {
								if (compAvlAttacks[i]) {
									attack(human, comp, i);
									break;
								}
							}
						}
					}
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				}
			}

			(*enemyTurnTimer) = 0;

		}

	}

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
MinionCard lordOfTheArena = MinionCard("Lord of the Arena", 6, 5, 6, true);
*/