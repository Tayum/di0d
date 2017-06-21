package automaton.Tests;

import automaton.SwitchFSM;
import automaton.TransTableFSM;
import automaton.StateFSM;

import static org.junit.Assert.assertEquals;

import org.junit.experimental.theories.DataPoints;
import org.junit.experimental.theories.Theories;
import org.junit.experimental.theories.Theory;
import org.junit.runner.RunWith;


@RunWith(Theories.class)
public class TheoriesTest {

	public SwitchFSM thyFSM = new SwitchFSM();
	// public TransTableFSM thyFSM = new TransTableFSM();
	// public StateFSM thyFSM = new StateFSM();
	
	@DataPoints
	public static Object[][] testData = new Object[][] {

		// Covers no Sharp and no At symbols
		{ false, "ALadsadKSDJ3787321" },

		// Covers no symbols in string at all
		{ false, "" },

		// Covers no Sharp symbol at the beginning
		{ false, "dladlasdl#@" },
		
		// Covers no At symbol
		{ false, "#" },
		
		// Covers the minimum required string containing both required symbols
		{ true, "#@" },

		// Covers letters not included among those we can use {a,b,c,d,e,f}
		{ false, "#JKL@" },

		// Covers the usage of both required symbols and also letters we can use
		{ true, "#abcabcabc@" },

		// Covers the usage of both required symbols and also digits we can use
		{ true, "#@3123213" },

		// Covers the mix of both letters and digits we can use (letters and then digits order)
		{ false, "#abcab35@" },

		// Covers the mix of both letters and digits we can use (digits and then letters order)
		{ false, "#@343243abc" },
		
		// Covers the usage of both required symbols and also letters and digits we can use
		// (separately: letters and then digits order)
		{ true, "#abcabcabcb@0348842384328" },
		
		// Covers the usage of both required symbols and also letters and digits we can use
		// (separately: digits and then letters order)
		{ true, "#03403402304@abcdef" }

	};

	@Theory
	public void testRegexp(final Object... testData) {
		final boolean actual = thyFSM.scanString((String)testData[1]);
		assertEquals(testData[0], actual);

	}
}