package automaton.StateFSM_Additional;

import automaton.Events;
import automaton.StateFSM;


public class Q6 implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		switch(curEvent) {
		case SHARP:
		case AT:
		case DIGIT:
		case OTHER:
		default:
			fsm.setState(new ERR());
			break;
		case LETTER:
			fsm.setState(new Q6());
			break;
		}
	}
	
	public String toString() {
		return "q6";
	}
}
