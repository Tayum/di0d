/*
// OLD EASY AI
// AI
void aiLogic(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton) {
	static bool avlAttacks = true;
	static bool avlSummon = true;

	if (comp->turn.isTurn()) {
		if ((*enemyTurnTimer) > 500) {
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
*/

/*
// IMPROVED AI WITHOUT DUPLICATES
// AI
void aiLogic(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton) {
	bool avlAttacks = false;
	bool avlSummon = false;

	if (comp->turn.isTurn()) {
		if ((*enemyTurnTimer) > 500) {
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
*/

/*
// IMPROVED AI WITH MORE DUPLICATES
// AI
void aiLogic(Player * human, Player * comp, float * enemyTurnTimer, Picture * endTurnButton) {
	bool avlAttacks = false;
	bool avlSummon = false;

	if (comp->turn.isTurn()) {
		if ((*enemyTurnTimer) > 500) {
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
			else if (avlAttacks == false && avlSummon == false) {
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

			// ATTACK
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

				// If comp has lethal
				if (isCompLethal) {
					// If there are taunts on battlefield
					if (human->bf.isThereTaunts()) {
						int targetHP = -1;
						int targetAttack = -1;
						int targetInd = -1;
						// Choosing first taunt target
						for (int i = 0; i < 7; i++) {
							if (humanTaunts[i]) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
								break;
							}
						}
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
						for (int i = 0; i < 7; i++) {
							if (compAvlAttacks[i]) {
								attack(human, comp, i);
								break;
							}
						}
					}
				}
				// If player has lethal
				else if (isPlayerLethal) {
					// If there are taunts on battlefield
					if (human->bf.isThereTaunts()) {
						int targetHP = -1;
						int targetAttack = -1;
						int targetInd = -1;
						// Finding target with taunt with biggest attack
						for (int i = 0; i < 7; i++) {
							if (humanTaunts[i] && humanAttacks[i] > targetAttack) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
							}
						}
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
				}
				// No one has lethal
				else {
					// If there are taunts on battlefield
					if (human->bf.isThereTaunts()) {
						int targetHP = -1;
						int targetAttack = -1;
						int targetInd = -1;
						// Choosing first taunt target
						for (int i = 0; i < 7; i++) {
							if (humanTaunts[i]) {
								targetHP = humanHP[i];
								targetAttack = humanAttacks[i];
								targetInd = i;
								break;
							}
						}
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
				}

			}

			(*enemyTurnTimer) = 0;

		}

	}

}
*/