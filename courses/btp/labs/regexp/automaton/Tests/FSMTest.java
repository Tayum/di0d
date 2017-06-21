package automaton.Tests;

import automaton.SwitchFSM;
import automaton.TransTableFSM;
import automaton.StateFSM;

import static org.junit.Assert.assertEquals;

import org.junit.Ignore;
import org.junit.Test;


public class FSMTest {

	public SwitchFSM thyFSM = new SwitchFSM();
	// public TransTableFSM thyFSM = new TransTableFSM();
	// public StateFSM thyFSM = new StateFSM();

	// Covers no Sharp and no At symbols
	@Test
	public void testNoSharpNoAt() {
		assertEquals(false, thyFSM.scanString("ALadsadKSDJ3787321"));
	}

	// Covers no symbols in string at all
	@Test
	public void testEmptyString() {
		assertEquals(false, thyFSM.scanString(""));
	}

	// Covers no Sharp symbol at the beginning
	@Test
	public void testWrongFirstSymbol() {
		assertEquals(false, thyFSM.scanString("dladlasdl#@"));
	}

	// Covers no At symbol
	@Test
	public void testNoAt() {
		assertEquals(false, thyFSM.scanString("#"));
	}

	// Covers the minimum required string containing both required symbols
	@Test
	public void testSharpAt() {
		assertEquals(true, thyFSM.scanString("#@"));
	}

	// Covers letters not included among those we can use {a,b,c,d,e,f}
	@Test
	public void testWrongLetter() {
		assertEquals(false, thyFSM.scanString("#JKL@"));
	}
	
	// Covers the usage of both required symbols and also letters we can use
	@Test
	public void testSharpLettersAt() {
		assertEquals(true, thyFSM.scanString("#abcabcabc@"));
	}
	
	// Covers the usage of both required symbols and also digits we can use
	@Test
	public void testSharpAtDigits() {
		assertEquals(true, thyFSM.scanString("#@3123213"));
	}
	
	// Covers the mix of both letters and digits we can use (letters and then digits order)
	@Test
	public void testMixLettersDigits() {
		assertEquals(false, thyFSM.scanString("#abcab35@"));
	}
	
	// Covers the mix of both letters and digits we can use (digits and then letters order)
	@Test
	public void testMixDigitsLetters() {
		assertEquals(false, thyFSM.scanString("#@343243abc"));
	}
	
	// Covers the usage of both required symbols and also letters and digits we can use
	// (separately: letters and then digits order)
	@Test
	public void testSharpLettersAtDigits() {
		assertEquals(true, thyFSM.scanString("#abcabcabcb@0348842384328"));
	}
	
	// Covers the usage of both required symbols and also letters and digits we can use
	// (separately: digits and then letters order)
	@Test
	public void SharpDigitsAtLetters() {
		assertEquals(true, thyFSM.scanString("#03403402304@abcdef"));
	}
}
