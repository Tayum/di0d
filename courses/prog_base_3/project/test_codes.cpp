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