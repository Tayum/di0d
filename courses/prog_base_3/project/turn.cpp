#include "turn.h"

Turn::Turn() {
	turn = false;
}

void Turn::start() {
	turn = true;
}

void Turn::end() {
	turn = false;
}

bool Turn::isTurn() {
	return turn;
}