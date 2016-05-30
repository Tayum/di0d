#ifndef TURN_H_INCLUDED
#define TURN_H_INCLUDED

class Turn {
	bool turn;
public:
	Turn();

	void start();
	void end();
	bool isTurn();
};

#endif // TURN_H_INCLUDED