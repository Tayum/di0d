package automaton;

public class SwitchFSM extends FSM {
	
	protected States nextState(Events curEvent) {
		switch (currentState) {
		case q0:
			switch(curEvent) {
			case SHARP:
				return States.q1;
			case AT:
			case DIGIT:
			case LETTER:
			case OTHER:
			default:
				return States.ERR;	
			}
		case q1:
			switch(curEvent) {
			case SHARP:
			case OTHER:
			default:
				return States.ERR;
			case AT:
				return States.q4;
			case DIGIT:
				return States.q2;
			case LETTER:
				return States.q3;	
			}
		case q2:
			switch(curEvent) {
			case SHARP:
			case LETTER:
			case OTHER:
			default:
				return States.ERR;
			case AT:
				return States.q4;
			case DIGIT:
				return States.q2;
			}
		case q3:
			switch(curEvent) {
			case SHARP:
			case DIGIT:
			case OTHER:
			default:
				return States.ERR;
			case AT:
				return States.q4;
			case LETTER:
				return States.q3;
			}
		case q4:
			switch(curEvent) {
			case SHARP:
			case AT:
			case OTHER:
			default:
				return States.ERR;
			case DIGIT:
				return States.q5;
			case LETTER:
				return States.q6;
			}
		case q5:
			switch(curEvent) {
			case SHARP:
			case AT:
			case LETTER:
			case OTHER:
			default:
				return States.ERR;
			case DIGIT:
				return States.q5;

			}
		case q6:
			switch(curEvent) {
			case SHARP:
			case AT:
			case DIGIT:
			case OTHER:
			default:
				return States.ERR;
			case LETTER:
				return States.q6;
			}
		case ERR:
		default:
			return States.ERR;
		}	
	}
}
