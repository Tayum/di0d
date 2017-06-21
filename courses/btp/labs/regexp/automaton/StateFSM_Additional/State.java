package automaton.StateFSM_Additional;

import automaton.StateFSM;
import automaton.Events;


public interface State {
	public void doAction(StateFSM fsm, Events curEvent);
}
