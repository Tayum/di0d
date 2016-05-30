/*
=====DECK-HAND TEST=====
srand(time(NULL));
Player firstPlayer(10, 10, 10, 7);
MinionCard card;

card = MinionCard("Murloc Raider", 2, 1, 1, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Magma Rager", 5, 1, 3, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Lord of the Arena", 6, 5, 6, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("War Golem", 7, 7, 7, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Core Hound", 9, 5, 7, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("River Crocolisk", 2, 3, 2, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
firstPlayer.deck.pushRand(card);
for (int i = 0; i < 11; i++) {
puts("\n=====FIRST PLAYER DECK GOES HERE=====");
firstPlayer.deck.printCards();
puts("\n=====================================\n");
puts("\n=====FIRST PLAYER HAND GOES HERE=====");
firstPlayer.hand.printCards();
puts("\n=====================================\n");
firstPlayer.startTurn();
}
*/

/*
=====HAND-BF TEST=====
srand(time(NULL));
Player firstPlayer(10, 10, 10, 7);
MinionCard card;

card = MinionCard("Murloc Raider", 2, 1, 1, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Magma Rager", 5, 1, 3, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("Lord of the Arena", 6, 5, 6, true);
firstPlayer.deck.pushRand(card);
card = MinionCard("War Golem", 7, 7, 7, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Core Hound", 9, 5, 7, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("River Crocolisk", 2, 3, 2, false);
firstPlayer.deck.pushRand(card);
card = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
firstPlayer.deck.pushRand(card);
for (int i = 0; i < 11; i++) {
firstPlayer.startTurn();
}
for (int i = 0; i < 11; i++) {
puts("\n=====FIRST PLAYER HAND GOES HERE=====");
firstPlayer.hand.printCards();
puts("\n=====================================\n");
firstPlayer.playCard(0);
puts("\n=====FIRST PLAYER BATTLEFIELD GOES HERE=====");
firstPlayer.bf.printCards();
puts("\n============================================\n");
firstPlayer.startTurn();
}*/

/*
=====BATTLEFIELD TEST=====
Battlefield myBF = Battlefield(7);
myBF.addLast(ogre);
myBF.printCards();
myBF.addLast(guardTree);
myBF.printCards();
myBF.delByInd(1);
myBF.printCards();
myBF.delByInd(0);
myBF.printCards();*/

/*
=====DECK TEST=====
Deck myDeck = Deck(30);
myDeck.push(ogre);
myDeck.push(guardTree);
MinionCard test = myDeck.pop();
test.printMinionCard();
test= myDeck.pop();
test.printMinionCard();
test = myDeck.pop();
test.printMinionCard();*/

/*
=====HAND TEST=====
Hand myHand = Hand(10, 10);
myHand.addLast(ogre);
myHand.addLast(guardTree);
MinionCard test = myHand.delByInd(0);
test.printMinionCard();
test = myHand.getByInd(1);
test.printMinionCard();
test = myHand.delByInd(0);
test.printMinionCard();
test = myHand.delByInd(0);
test.printMinionCard();*/

/*
=====MINION CARD TEST=====
ogre.printMinionCard();
guardTree.printMinionCard();
ogre.attack(guardTree);
ogre.printMinionCard();
guardTree.printMinionCard();*/

/*
=====PLAYER CLASS TEST=====
	srand(time(NULL));
	Player firstPlayer(10, 10, 10, 7);
	MinionCard card;

	card = MinionCard("Murloc Raider", 2, 1, 1, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Frostwolf Grunt", 2, 2, 2, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Magma Rager", 5, 1, 3, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Sen'jin Shieldmasta", 3, 5, 4, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Booty Bay Bodyguard", 5, 4, 5, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Lord of the Arena", 6, 5, 6, true);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("War Golem", 7, 7, 7, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Core Hound", 9, 5, 7, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("River Crocolisk", 2, 3, 2, false);
	firstPlayer.deck.pushRand(card);
	card = MinionCard("Ironfur Grizzly", 3, 3, 3, true);
	firstPlayer.deck.pushRand(card);
	for (int i = 0; i < 11; i++) {
		firstPlayer.startTurn();
	}
	for (int i = 0; i < 11; i++) {
		puts("\n=====FIRST PLAYER HAND GOES HERE=====");
		firstPlayer.hand.printCards();
		puts("\n=====================================\n");
		firstPlayer.playCard(0);
		puts("\n=====FIRST PLAYER BATTLEFIELD GOES HERE=====");
		firstPlayer.bf.printCards();
		puts("\n============================================\n");
		firstPlayer.startTurn();
	}
	getch();
	return 0;
*/

/*
=====ALL TEXT POSITIONS AND STYLES
Font font;
font.loadFromFile("font/CyrilicOld.TTF");

Text hpEnemy("", font, 30);
Text curManaEnemy("", font, 25);
Text maxManaEnemy("", font, 25);
Text handEnemy("", font, 25);
Text deckEnemy("", font, 25);
Text hpPlayer("", font, 30);
Text curManaPlayer("", font, 25);
Text maxManaPlayer("", font, 25);
Text handPlayer("", font, 25);
Text deckPlayer("", font, 25);

hpEnemy.setColor(Color::Red);
curManaEnemy.setColor(Color::Cyan);
maxManaEnemy.setColor(Color::Blue);
handEnemy.setColor(Color::Green);
deckEnemy.setColor(Color::Yellow);
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

========================================

**************
buff << player.getMana();
**************

ostringstream buff;
buff.str("");
buff << "11";
hpEnemy.setString("" + buff.str());
hpEnemy.setPosition(0, 0);
buff.str("");
buff << "22";
curManaEnemy.setString("" + buff.str());
curManaEnemy.setPosition(0, 64);
buff.str("");
buff << "33";
maxManaEnemy.setString("" + buff.str());
maxManaEnemy.setPosition(0, 128);
buff.str("");
buff << "44";
handEnemy.setString("" + buff.str());
handEnemy.setPosition(96, 0);
buff.str("");
buff << "55";
deckEnemy.setString("" + buff.str());
deckEnemy.setPosition(96, 128);
buff.str("");
buff << "66";
hpPlayer.setString("" + buff.str());
hpPlayer.setPosition(0, 480);
buff.str("");
buff << "77";
curManaPlayer.setString("" + buff.str());
curManaPlayer.setPosition(0, 544);
buff.str("");
buff << "88";
maxManaPlayer.setString("" + buff.str());
maxManaPlayer.setPosition(0, 608);
buff.str("");
buff << "99";
handPlayer.setString("" + buff.str());
handPlayer.setPosition(96, 480);
buff.str("");
buff << "00";
deckPlayer.setString("" + buff.str());
deckPlayer.setPosition(96, 608);
*/

/*
=====CARDS POSITIONS TEST=====
Picture testPic = Picture("murlocRaider.png", 0, 0, 286, 395);
MinionCard test = MinionCard(testPic, "Murloc Raider", 2, 1, 1, false);

**************************FOR BF (ENEMY/PLAYER)******************************
test.pic.sprite.setScale(0.671, 0.405); //FOR BF!
//ENEMY
test.pic.sprite.setPosition(192*POSITION, 160); //POSITION IS POSITION ON THE BOARD (0-6)
//PLAYER
test.pic.sprite.setPosition(192*POSITION, 320); //POSITION IS POSITION ON THE BOARD (0-6)

**************************FOR HAND (PLAYER)******************************
//test.pic.sprite.setScale(0.405, 0.425);	//FOR HAND!
//PLAYER
//test.pic.sprite.setPosition(128*(POSITION+1), 480);	//POSITION IS POSITION IN THE HAND (0-9)
*/