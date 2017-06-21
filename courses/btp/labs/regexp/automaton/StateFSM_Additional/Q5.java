package automaton.StateFSM_Additional;

import automaton.Events;
import automaton.StateFSM;

public class Q5 implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		switch(curEvent) {
		case SHARP:
		case AT:
		case LETTER:
		case OTHER:
		default:
			fsm.setState(new ERR());
			break;
		case DIGIT:
			fsm.setState(new Q5());
			break;
		}
	}
	
	public String toString() {
		return "q5";
	}

}
