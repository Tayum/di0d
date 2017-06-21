package automaton.StateFSM_Additional;

import automaton.Events;
import automaton.StateFSM;

public class Q4 implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		switch(curEvent) {
		case SHARP:
		case AT:
		case OTHER:
		default:
			fsm.setState(new ERR());
			break;
		case DIGIT:
			fsm.setState(new Q5());
			break;
		case LETTER:
			fsm.setState(new Q6());
			break;
		}
	}
	
	public String toString() {
		return "q4";
	}

}
