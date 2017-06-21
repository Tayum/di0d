import Jama.*;

import java.util.NoSuchElementException;
import java.util.Scanner;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class MatricesRunner 
{
	public static void main( String[] args) throws Exception 
	{
		System.out.println("VARIANT #10");
		System.out.println("EXPRESSION: (A+B^T)*rank(C)");
		System.out.println("EXPRESSION IN TERMS OF PROGRAM: (A-B^T)*C^R\n");
		System.out.println("SYNTAX:");
		System.out.println("MATRIX: [[1,2.5,3];[4.20;5;6.66]]");
		System.out.println("VARIABLE = VARIABLE | (expression) | MATRIX");
		System.out.println("PLUS: MATRIX + MATRIX e.g. [[1,2,3];[4;5;6]] + [[7,8,9];[10;11;12]]");
		System.out.println("MINUS: MATRIX - MATRIX e.g. [[1,2,3];[4;5;6]] - [[7,8,9];[10;11;12]]");
		System.out.println("TRANSPOSE: MATRIX^T e.g. [[1,2,3];[4;5;6]]^T");
		System.out.println("RANK: MATRIX^R e.g. [[7,8,9];[10;11;12]]^R");
		System.out.println("MULTIPLICATION: MATRIX*(NUMBER | MATRIX) e.g. [[1,2,3];[4;5;6]]*[[7,8,9];[10;11;12]]^R");
		



	    Scanner scanner = new Scanner(System.in);
        MatricesBaseVisitorImp instance = new MatricesBaseVisitorImp();

        while(true) {
        	System.out.print("\n\n> ");
        	String input_string = scanner.nextLine();
        	if(input_string.isEmpty()) {
        		continue;
        	}
        	else if("quit".equals(input_string)) {
        		scanner.close();
        		break;
        	}
            ANTLRInputStream input = new ANTLRInputStream(input_string);
            MatricesLexer lexer = new MatricesLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            MatricesParser parser = new MatricesParser(tokens);
            
            // Error handler for ANTLR to prevent input to be parsed
            // after first invalid input
            parser.setErrorHandler(new DefaultErrorStrategy() {
//                @Override
//                public void recover(Parser recognizer, RecognitionException e) {
//                    throw new IllegalArgumentException("Invalid input according to grammar (recover)");
//                }
                @Override
                public Token recoverInline(Parser recognizer) {
                    throw new IllegalArgumentException("Invalid input according to grammar (recoverInline)");
                }
                @Override
                public void reportError(Parser recognizer, RecognitionException e) {
                    throw new IllegalArgumentException("Invalid input according to grammar (reportError)");
                }
            });
            
            try {
            	// handle error in input
            	ParseTree tree = parser.root();
            	// illegal argument exceptions OR 'null's
                Matrix result = instance.visit(tree);
            	result.print(1, 2);
            }
            catch (IllegalArgumentException | NoSuchElementException e) {
            	System.out.println(e.getMessage());
            }
            catch (NullPointerException e) {
            	System.out.println(e.getMessage());
            }
        }
	}
}