package automaton;

public class Main {
	
	public static void main(String[] args) {
		// conditions
		System.out.println("VARIANT ¹10\n");
		System.out.println("Regular Exspression: #(\\d*|[a-f]*)@(\\d*|[a-f]*)\n");
		final String[] CASES = {
				"ALadsadKSDJ3787321",
				"",
				"dladlasdl#@",
				"#",
				"#@",
				"#JKL@",
				"#abcabcabc@",
				"#@3123213",
				"#abcab35@",
				"#@343243abc",
				"#abcabcabcb@0348842384328",
				"#03403402304@abcdef",
		};
		
		// I: SWITCH FSM
		System.out.println("==========SWITCH FSM==========\n");
		SwitchFSM switchFsm = new SwitchFSM();
		for (int i = 0; i < CASES.length; i++) {
			System.out.println("{" + CASES[i] + "} -- " + switchFsm.scanString(CASES[i]));
		}
		System.out.println();
		
		// II: TRANS TABLE FSM
		System.out.println("==========TRANS TABLE FSM==========\n");
		TransTableFSM transtableFsm = new TransTableFSM();
		for (int i = 0; i < CASES.length; i++) {
			System.out.println("{" + CASES[i] + "} -- " + transtableFsm.scanString(CASES[i]));
		}
		System.out.println();
		
		/// III: STATE FSM
		System.out.println("==========STATE FSM==========\n");
		StateFSM stateFsm = new StateFSM();
		for (int i = 0; i < CASES.length; i++) {
			System.out.println("{" + CASES[i] + "} -- " + stateFsm.scanString(CASES[i]));
			stateFsm.start();
		}
		System.out.println();
	}
	
}