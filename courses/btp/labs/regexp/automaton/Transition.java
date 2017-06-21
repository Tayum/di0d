package automaton;

public class Transition {
	protected States startEvent;
	protected Events trigger;
	protected States endEvent;
	
	public Transition(States stEv, Events tr, States endEv) {
		startEvent = stEv;
		trigger = tr;
		endEvent = endEv;
	}
}
