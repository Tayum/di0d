package automaton;

import java.util.LinkedList;
import java.util.Iterator;

public class TransTableFSM extends FSM {
	LinkedList<Transition> transitions;
	
	public TransTableFSM() {
		transitions = new LinkedList<Transition>();
		buildTransitionTable();
	}
	
	public void buildTransitionTable() {
		transitions.add(new Transition(States.q0, Events.SHARP, States.q1));
		transitions.add(new Transition(States.q1, Events.AT, States.q4));
		transitions.add(new Transition(States.q1, Events.DIGIT, States.q2));
		transitions.add(new Transition(States.q1, Events.LETTER, States.q3));
		transitions.add(new Transition(States.q2, Events.AT, States.q4));
		transitions.add(new Transition(States.q2, Events.DIGIT, States.q2));
		transitions.add(new Transition(States.q3, Events.AT, States.q4));
		transitions.add(new Transition(States.q3, Events.LETTER, States.q3));
		transitions.add(new Transition(States.q4, Events.DIGIT, States.q5));
		transitions.add(new Transition(States.q4, Events.LETTER, States.q6));
		transitions.add(new Transition(States.q5, Events.DIGIT, States.q5));
		transitions.add(new Transition(States.q6, Events.LETTER, States.q6));
	}
	
	protected States nextState(Events curEvent) {
		Iterator<Transition> iter = transitions.iterator();
		while (iter.hasNext()) {
			Transition thyTransition = iter.next();
			if (currentState == thyTransition.startEvent && curEvent == thyTransition.trigger) {
				return thyTransition.endEvent;
			}
		}
		return States.ERR;
	}
}
