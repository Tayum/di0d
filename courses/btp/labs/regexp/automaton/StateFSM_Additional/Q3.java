package automaton.StateFSM_Additional;

import automaton.Events;
import automaton.StateFSM;

public class Q3 implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		switch(curEvent) {
		case SHARP:
		case DIGIT:
		case OTHER:
		default:
			fsm.setState(new ERR());
			break;
		case AT:
			fsm.setState(new Q4());
			break;
		case LETTER:
			fsm.setState(new Q3());
			break;
		}
	}
	
	public String toString() {
		return "q3";
	}
}
