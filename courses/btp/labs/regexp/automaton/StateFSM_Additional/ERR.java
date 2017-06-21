package automaton.StateFSM_Additional;

import automaton.Events;
import automaton.StateFSM;

public class ERR implements State {
	public void doAction(StateFSM fsm, Events curEvent) {
		fsm.setState(new ERR());
	}
	
	public String toString() {
		return "ERR";
	}
}
