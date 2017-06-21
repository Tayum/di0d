package automaton.StateFSM_Additional;

import automaton.StateFSM;
import automaton.Events;

public class Q0 implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		switch(curEvent) {
		case SHARP:
			fsm.setState(new Q1());
			break;
		case AT:
		case DIGIT:
		case LETTER:
		case OTHER:
		default:
			fsm.setState(new ERR());
			break;
		}
	}
	
	public String toString() {
		return "q0";
	}
}
