#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <time.h>

#include <SFML/Audio.hpp>

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

int main(void) {
	srand(time(NULL));
	Clock clock;
	clock.restart();
	Picture background = Picture("backgroundTilesets.png", 0, 0, 128, 32);
	
	//===============FONT
	Font font;
	font.loadFromFile("font/CyrilicOld.TTF");
	Text heroNameEnemy("", font, 20);
	Text hpEnemy("", font, 30);
	Text curManaEnemy("", font, 25);
	Text maxManaEnemy("", font, 25);
	Text handEnemy("", font, 25);
	Text deckEnemy("", font, 25);
	Text heroNamePlayer("", font, 25);
	Text hpPlayer("", font, 30);
	Text curManaPlayer("", font, 25);
	Text maxManaPlayer("", font, 25);
	Text handPlayer("", font, 25);
	Text deckPlayer("", font, 25);
	Text bfTextPlayer[7];
	for (int i = 0; i < 7; i++) {
		bfTextPlayer[i] = Text("", font, 18);
		bfTextPlayer[i].setString("ATTACK");
	}
	Text bfHPTextPlayer[7];
	Text bfHPTextEnemy[7];
	for (int i = 0; i < 7; i++) {
		bfHPTextPlayer[i] = Text("", font, 25);
		bfHPTextPlayer[i].setStyle(Text::Bold);
		bfHPTextEnemy[i] = Text("", font, 25);
		bfHPTextEnemy[i].setStyle(Text::Bold);
	}

	heroNameEnemy.setColor(Color::White);
	hpEnemy.setColor(Color::Red);
	curManaEnemy.setColor(Color::Cyan);
	maxManaEnemy.setColor(Color::Blue);
	handEnemy.setColor(Color::Green);
	deckEnemy.setColor(Color::Yellow);
	heroNamePlayer.setColor(Color::White);
	hpPlayer.setColor(Color::Red);
	curManaPlayer.setColor(Color::Cyan);
	maxManaPlayer.setColor(Color::Blue);
	handPlayer.setColor(Color::Green);
	deckPlayer.setColor(Color::Yellow);
	hpEnemy.setStyle(Text::Bold);
	curManaEnemy.setStyle(Text::Italic);
	maxManaEnemy.setStyle(Text::Bold);
	handEnemy.setStyle(Text::Italic);
	deckEnemy.setStyle(Text::Bold);
	hpPlayer.setStyle(Text::Bold);
	curManaPlayer.setStyle(Text::Italic);
	maxManaPlayer.setStyle(Text::Bold);
	handPlayer.setStyle(Text::Italic);
	deckPlayer.setStyle(Text::Bold);
	//===============FONT_END
	std::cout << "Loaded font: " << clock.restart().asMilliseconds() << " millisec taken;\n";

	//===============DECK_INIT
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
	int allHP[] =	  { 2,4,7,5,5,2,2,3,5,1,1,7,3,5,4,7 };
	int allManacost[] { 2,5,6,4,7,2,1,3,6,3,1,4,2,4,3,7 };
	bool allTaunt[] = { false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,false };
	MinionCard allCards[ALL_CARDS];

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
	//===============DECK_INIT_END
	std::cout << "Deck initialized: " << clock.restart().asMilliseconds() << " millisec taken;\n";

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
	bfHeart.sprite.setScale(0.475, 0.307);
	//===============BF HEART_END

	//===============PLAYER_INIT
	Picture picBuffHuman = Picture("jaina.png", 0, 0, 200, 200);
	Player human = Player("Jaina", &picBuffHuman);
	human.hero.pic->sprite.setScale(0.48, 0.48);
	Picture picBuffComp = Picture("guldan.png", 0, 0, 200, 200);
	Player comp = Player("Gul'dan", &picBuffComp);
	comp.hero.pic->sprite.setScale(0.48, 0.48);
	//===============
	std::cout << "Players created: " << clock.restart().asMilliseconds() << " millisec taken;\n";
	//===============
	// Deck prep for players
	human.deck.prepare(allCards);
	comp.deck.prepare(allCards);
	//===============PLAYER_INIT_END
	std::cout << "Players' decks prepared: " << clock.restart().asMilliseconds() << " millisec taken;\n";

	//===============ENEMY AI
	bool avlAttacks = true;
	bool avlSummon = true;
	//===============ENEMY AI_END

	//===============MOUSE CONTROL
	bool isClicked = false;
	clickType type = HAND;
	int indFirstClick = 0;
	Vector2i mouseClickPos;
	//===============MOUSE CONTROL_END

	RenderWindow window(sf::VideoMode(1344, 640), "Candlehearth");	// 1366*768 is native, sf::Style::Fullscreen

	//===============MAIN MENU
	mainMenu(&window);
	//===============MAIN MENU_END

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
							if (IntRect(0, 160, 1344, 320).contains(mouseClickPos.x, mouseClickPos.y)) {
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
		window.clear(); // Clear the window

		// AI
		if (comp.turn.isTurn()) {
			if (enemyTurnTimer > 500) {
				// ATTACK
				if (avlAttacks) {
					for (int i = 0; i <= comp.bf.getCurCardAmount(); i++) {
						if (i == comp.bf.getCurCardAmount()) {
							avlAttacks = false;
							break;
						}
						else if (comp.bf.cardList[i].hasAttacked() == false) {
							if (human.bf.isThereTaunts()) {
								for (int j = 0; j < human.bf.getCurCardAmount(); j++) {
									if (human.bf.cardList[j].getTaunt()) {
										attack(&human, &comp, i, j);
										break;
									}
								}
							}
							else {
								attack(&human, &comp, i);
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
					if (comp.bf.isFull() == false && comp.hand.isEmpty() == false) {
						for (int i = 0; i < comp.hand.getCurCardAmount(); i++) {
							if (comp.hand.mana.isEnough(comp.hand.cardList[i].getManacost()) && comp.hand.cardList[i].getManacost() > maxMana) {
								maxMana = comp.hand.cardList[i].getManacost();
								maxManaIndex = i;
							}
						}
						if (maxMana != -1 && maxManaIndex != -1) {
							comp.playCard(maxManaIndex);
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
					endTurnButton.sprite.setTextureRect(IntRect(0, 0, 160, 160));

					endTurn(&human, &comp);
				}

				enemyTurnTimer = 0;
				
				for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
					human.bf.cardList[i].pic->sprite.setColor(Color::White);
				}
				human.hero.pic->sprite.setColor(Color::White);
				for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
					comp.bf.cardList[i].pic->sprite.setColor(Color::White);
				}
			}

		}


		// Draw: Background
		for (int i = 0; i < HEIGHT_BG; i++) {
			for (int j = 0; j < WIDTH_BG; j++) {
				if (bgTile[i][j] == 'h') {
					background.sprite.setTextureRect(IntRect(96, 0, 32, 32));
				}
				else if (bgTile[i][j] == 'c') {
					background.sprite.setTextureRect(IntRect(64, 0, 32, 32));
				}
				else if ((bgTile[i][j] == 'b')) {
					background.sprite.setTextureRect(IntRect(0, 0, 32, 32));
				}
				else if ((bgTile[i][j] == ' ')) {
					background.sprite.setTextureRect(IntRect(32, 0, 32, 32));
				}
				background.sprite.setPosition(j * 32, i * 32);
				window.draw(background.sprite);
			}
		}

		// Draw: Cards (enemy BF, human BF (+ attack state, BF hearts, curHP), human Hand)
		std::ostringstream buff;
		for (int i = 0; i < comp.bf.getCurCardAmount(); i++) {
			comp.bf.cardList[i].pic->sprite.setPosition(192 * i, 160);
			window.draw(comp.bf.cardList[i].pic->sprite);

			bfHeart.sprite.setPosition(192 * i + 150, 290);
			window.draw(bfHeart.sprite);

			buff.str("");
			buff << comp.bf.cardList[i].getCurHealth();
			bfHPTextEnemy[i].setString("" + buff.str());
			bfHPTextEnemy[i].setPosition(192 * i + 160, 288);
			window.draw(bfHPTextEnemy[i]);
		}
		for (int i = 0; i < human.bf.getCurCardAmount(); i++) {
			human.bf.cardList[i].pic->sprite.setPosition(192 * i, 320);
			window.draw(human.bf.cardList[i].pic->sprite);

			if (human.bf.cardList[i].hasAttacked() == false) {
				bfTextPlayer[i].setColor(Color::Green);
			}
			else {
				bfTextPlayer[i].setColor(Color::Red);
			}
			bfTextPlayer[i].setPosition(192 * i + 62, 452);
			window.draw(bfTextPlayer[i]);

			bfHeart.sprite.setPosition(192 * i + 150, 450);
			window.draw(bfHeart.sprite);

			buff.str("");
			buff << human.bf.cardList[i].getCurHealth();
			bfHPTextPlayer[i].setString("" + buff.str());
			bfHPTextPlayer[i].setPosition(192 * i + 160, 448);
			window.draw(bfHPTextPlayer[i]);
		}
		for (int i = 0; i < human.hand.getCurCardAmount(); i++) {
			human.hand.cardList[i].pic->sprite.setPosition(128 * (i + 1), 480);
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
		human.hero.pic->sprite.setPosition(32, 512);
		window.draw(human.hero.pic->sprite);

		buff.str("");
		buff << human.hero.getName();
		heroNamePlayer.setString("" + buff.str());
		heroNamePlayer.setPosition(32, 480);
		window.draw(heroNamePlayer);

		// Draw: info about player
		// enemy
		buff.str("");
		buff << comp.hero.getCurHP();
		hpEnemy.setString("" + buff.str());
		hpEnemy.setPosition(0, 0);

		buff.str("");
		buff << comp.hand.mana.getCurMana();
		curManaEnemy.setString("" + buff.str());
		curManaEnemy.setPosition(0, 64);

		buff.str("");
		buff << comp.hand.mana.getCurMaxMana();
		maxManaEnemy.setString("" + buff.str());
		maxManaEnemy.setPosition(0, 128);

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
		hpPlayer.setPosition(0, 480);

		buff.str("");
		buff << human.hand.mana.getCurMana();
		curManaPlayer.setString("" + buff.str());
		curManaPlayer.setPosition(0, 544);

		buff.str("");
		buff << human.hand.mana.getCurMaxMana();
		maxManaPlayer.setString("" + buff.str());
		maxManaPlayer.setPosition(0, 608);

		buff.str("");
		buff << human.hand.getCurCardAmount();
		handPlayer.setString("" + buff.str());
		handPlayer.setPosition(96, 480);

		buff.str("");
		buff << human.deck.getCurCardAmount();
		deckPlayer.setString("" + buff.str());
		deckPlayer.setPosition(96, 608);

		window.draw(hpEnemy);
		window.draw(curManaEnemy);
		window.draw(maxManaEnemy);
		window.draw(handEnemy);
		window.draw(deckEnemy);
		window.draw(hpPlayer);
		window.draw(curManaPlayer);
		window.draw(maxManaPlayer);
		window.draw(handPlayer);
		window.draw(deckPlayer);

		window.display(); // Display the window's draws

	}

	// End of program
	return 0;
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