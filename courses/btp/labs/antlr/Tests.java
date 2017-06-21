import static org.junit.Assert.assertEquals;

import java.util.NoSuchElementException;
import java.util.Arrays;

import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.junit.Test;

import Jama.Matrix;

public class Tests {
	MatricesBaseVisitorImp instance = new MatricesBaseVisitorImp();
    ANTLRInputStream input;
    MatricesLexer lexer;
    CommonTokenStream tokens;
    MatricesParser parser;
    ParseTree tree; 	

    
    // Returns the inner double[][] array of received Matrix
 	public double[][] prepareToTest(String string_to_analyze) {
 	    input = new ANTLRInputStream(string_to_analyze);
 	    lexer = new MatricesLexer(input);
 	    tokens = new CommonTokenStream(lexer);
 	    parser = new MatricesParser(tokens);
 	    tree = parser.root();
 	    Matrix toCompare = null;
 	    try {
 	 	    toCompare = instance.visit(tree);
 		    return toCompare.getArrayCopy();
 	    }
 	    catch (IllegalArgumentException | NoSuchElementException e) {
 	    	throw e;
 	    }
 	    catch (NullPointerException e) {
 	    	throw e;
 	    }
 	}
 	
	// Covers MATRIX + MATRIX operation
	@Test
	public void testPlus() {
		double[][] toCompare = new double[3][3];
		toCompare[0][0] = 11;
		toCompare[0][1] = 13;
		toCompare[0][2] = 15;
		toCompare[1][0] = 17;
		toCompare[1][1] = 19;
		toCompare[1][2] = 21;
		toCompare[2][0] = 23;
		toCompare[2][1] = 25;
		toCompare[2][2] = 27;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[1,2,3];[4,5,6];[7,8,9]]+[[10,11,12];[13,14,15];[16,17,18]]"), toCompare));
	}

	// Covers MATRIX - MATRIX operation
	@Test
	public void testMinus() {
		double[][] toCompare = new double[2][2];
		toCompare[0][0] = -8;
		toCompare[0][1] = -9;
		toCompare[1][0] = -10;
		toCompare[1][1] = -11;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[1,1];[1,1]]-[[9,10];[11,12]]"), toCompare));
	}

	// Covers MATRIX * NUMBER operation
	@Test
	public void testMatrixMultNumber() {
		double[][] toCompare = new double[1][2];
		toCompare[0][0] = 500;
		toCompare[0][1] = 1001;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[100,200.2]]*5"), toCompare));
	}

	// Covers NUMBER * MATRIX operation
	@Test
	public void testNumberMultMatrix() {
		double[][] toCompare = new double[2][1];
		toCompare[0][0] = 100;
		toCompare[1][0] = 200;
		assertEquals(true, Arrays.deepEquals(prepareToTest("10*[[10];[20]]"), toCompare));
	}

	// Covers MATRIX^R (rank) operation
	@Test
	public void testRank() {
		int rank = 1;
		assertEquals(true, prepareToTest("[[1,1,1]]^R")[0][0] == rank);
	}

	// Covers MATRIX * MATRIX^R operation
	@Test
	public void testMatrixMultRank() {
		double[][] toCompare = new double[3][2];
		toCompare[0][0] = 100;
		toCompare[0][1] = 200;
		toCompare[1][0] = 300;
		toCompare[1][1] = 400;
		toCompare[2][0] = 500;
		toCompare[2][1] = 600;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[50,100];[150,200];[250,300]]*[[2,3,7,11];[1,2,4,7];[5,0,10,5]]^R"), toCompare));
	}
	
	// Covers MATRIX^R * MATRIX operation
	@Test
	public void testRankMultMatrix() {
		double[][] toCompare = new double[2][3];
		toCompare[0][0] = 40;
		toCompare[0][1] = 80;
		toCompare[0][2] = 120;
		toCompare[1][0] = 160;
		toCompare[1][1] = 200;
		toCompare[1][2] = 240;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[1,1,1,1,0];[1,2,1,1,0];[1,1,3,1,0];[1,1,1,4,0];[1,2,3,4,0]]^R*[[10,20,30];[40,50,60]]"), toCompare));
	}
	
	// Covers MATRIX^T (transpose) operation
	@Test
	public void testSharpAtDigits() {
		double[][] toCompare = new double[3][1];
		toCompare[0][0] = 10;
		toCompare[1][0] = 20;
		toCompare[2][0] = 30;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[10,20,30]]^T"), toCompare));
	}
	
	// Covers (MATRIX-MATRIX^T) expression
	@Test
	public void testHalfOfExpression() {
		double[][] toCompare = new double[1][3];
		toCompare[0][0] = 50;
		toCompare[0][1] = 60;
		toCompare[0][2] = 70;
		assertEquals(true, Arrays.deepEquals(prepareToTest("[[100,200,300]]-[[50];[140];[230]]^T"), toCompare));
	}
	
	// Covers (MATRIX-MATRIX^T)*MATRIX^R (full coverage of task's expression)
	@Test
	public void testFullExpression() {
		double[][] toCompare = new double[2][2];
		toCompare[0][0] = 4;
		toCompare[0][1] = 6;
		toCompare[1][0] = 8;
		toCompare[1][1] = 10;
		assertEquals(true, Arrays.deepEquals(prepareToTest("([[3,4];[5,6]]-[[1,1];[1,1]]^T)*[[2,3,7,11];[1,2,4,7];[5,0,10,5]]^R"), toCompare));
	}
	
	// Covers the usage of the undeclared variable
	// CHECKS THROWN EXCEPTION
	@Test (expected = NoSuchElementException.class)
	public void testCatchUndeclaredVariable() {
		prepareToTest("a");
	}
	
	// Covers creating the invalid matrix
	// CHECKS THROWN EXCEPTION
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidMatrix() {
		prepareToTest("[[1,2,3,4,5];[1,2,3,4]]");
	}
	
	// Covers invalid dimensions while performing PLUS operation
	// CHECKS THROWN EXCEPTION
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidDimensionsPlus() {
		prepareToTest("[[1,2,3];[4,5,6]]+[[1,2,3];[4,5,6];[7,8,9]]");
	}
	
	// Covers invalid dimensions while performing MINUS operation
	// CHECKS THROWN EXCEPTION
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidDimensionsMinus() {
		prepareToTest("[[1,2];[3,4];[4,5]]-[[1,2,3];[4,5,6];[7,8,9]]");
	}
	
	// Covers invalid dimensions while performing MULT operation
	// CHECKS THROWN EXCEPTION
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidDimensionsMult() {
		prepareToTest("[[1,2];[3,4];[5,6]]*[[1,2,3];[4,5,6];[7,8,9]]");
	}
	
}
