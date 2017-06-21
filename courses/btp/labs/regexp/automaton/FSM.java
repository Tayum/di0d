package automaton;

public class FSM {
	protected States currentState;
	
	public FSM() {
		currentState = States.q0;
	}
	
	private void start() {
		currentState = States.q0;
	}
	
	private Events recognizeEvent(char curSymbol) {
		switch(curSymbol) {
		case '#':
			return Events.SHARP;
		case '@':
			return Events.AT;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return Events.DIGIT;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			return Events.LETTER;
		default:
			return Events.OTHER;
		}

	}
	
	public boolean scanString(String thyString) {
		start();
		for (int i = 0; i < thyString.length(); i++) {
			Events curEvent = recognizeEvent(thyString.charAt(i));
			currentState = nextState(curEvent);
			if (currentState == States.ERR) {
				return false;
			}
		}
		if(currentState != States.q4 && currentState != States.q5 && currentState != States.q6) {
			return false;
		}
		else {
			return true;
		}
	}
	
	protected States nextState(Events curEvent) {
		return States.ERR;
	}
	
}
