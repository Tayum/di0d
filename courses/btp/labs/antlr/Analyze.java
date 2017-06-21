import java.util.HashMap;
import java.util.NoSuchElementException;

import Jama.*;

class MatricesBaseVisitorImp extends MatricesBaseVisitor<Matrix> {
	private HashMap<String, Matrix> variables = new HashMap<String, Matrix>();

    @Override
    public Matrix visitRootRule(MatricesParser.RootRuleContext ctx) {
    	System.out.println("visit root rule");
    	return visit(ctx.input().getChild(0));
    }
	
    @Override
    public Matrix visitPlus(MatricesParser.PlusContext ctx) {
    	System.out.println("visit plus");
    	try {
    		Matrix toReturn = visit(ctx.plusOrMinus()).plus(visit(ctx.mult()));
    		return toReturn;
    	}
		catch (IllegalArgumentException e) {
			throw new IllegalArgumentException("\nInvalid dimensions while performing '+' operation");
		}
    }
    
    @Override
    public Matrix visitMinus(MatricesParser.MinusContext ctx) {
    	System.out.println("visit minus");
    	try {
    		Matrix toReturn = visit(ctx.plusOrMinus()).minus(visit(ctx.mult()));
    		return toReturn;
    	}
		catch (IllegalArgumentException e) {
			throw new IllegalArgumentException("\nInvalid dimensions while performing '-' operation");
		}
    }

    @Override
    public Matrix visitMultiplication(MatricesParser.MultiplicationContext ctx) {
    	System.out.println("visit multiplication");
    	try {
            // return visit(ctx.mult()).times(visit(ctx.rnk()).get(0, 0));
    		Matrix firstMatrix = visit(ctx.mult());
    		Matrix secondMatrix = visit(ctx.rnk());
    		// if first operand is matrix and second operand is rank of matrix 
    		if(firstMatrix.getRowDimension() == 1 && firstMatrix.getColumnDimension() == 1) {
    			return secondMatrix.times(firstMatrix.get(0, 0));
    		}
    		// if first operand is rank of matrix and second operand is matrix
    		else if(secondMatrix.getRowDimension() == 1 && secondMatrix.getColumnDimension() == 1) {
    			return firstMatrix.times(secondMatrix.get(0, 0));
    		}
    		// if it's matrix that is multiplied by another matrix
    		else {
    			return firstMatrix.times(secondMatrix);
    		}
    	}
    	catch (IllegalArgumentException e) {
    		throw new IllegalArgumentException("\nInvalid dimensions while performing '*' operation");
    	}
    }
    
    // Multiplication on number
    @Override
    public Matrix visitMultiplicationByNumber(MatricesParser.MultiplicationByNumberContext ctx) {
    	System.out.println("visit multiplication by number");
    		Double num = Double.parseDouble(ctx.NUMBER().getText());
            return visit(ctx.mult()).times(num);
    }

    @Override
    public Matrix visitSetVariable(MatricesParser.SetVariableContext ctx) {
    	System.out.println("visit set variable");
	        Matrix value = visit(ctx.input());
	        if(value != null) {
	            variables.put(ctx.VAR().getText(), value);
	        }
	        else {
	        	throw new IllegalArgumentException("An attempt to assign 'NULL' value to variable, refused it");
	        }
	        return value;
    }
    
    @Override
    public Matrix visitRank(MatricesParser.RankContext ctx) {
    	System.out.println("visit rank");
			if(ctx.RNK() != null) {
				int rank = visit(ctx.trans()).rank();
				double[][] arr = new double[1][1];
				arr[0][0] = rank;
				return new Matrix(arr);
			}
	    	return visit(ctx.trans());
    }
    
    @Override
    public Matrix visitTranspose(MatricesParser.TransposeContext ctx) {
    	System.out.println("visit transpose");
			if(ctx.TRANS() != null) {
				return visit(ctx.atom()).transpose();
			}
	    	return visit(ctx.atom());
    }

    @Override
    public Matrix visitBraces(MatricesParser.BracesContext ctx) {
    	System.out.println("visit braces");
    		return visit(ctx.plusOrMinus());
    }

    @Override
    public Matrix visitMatrix(MatricesParser.MatrixContext ctx) {
    	System.out.println("visit matrix");
		String matrix_string = ctx.getText();
		matrix_string = matrix_string.replace("[", "").replace("]", "");
		
		String[] vector_arr = matrix_string.split(";");
		double[][] arr = new double[vector_arr.length][];
		for(int i = 0; i < vector_arr.length; i++) {
			String[] numbers = vector_arr[i].split(",");
			arr[i] = new double[numbers.length];
			for(int j = 0; j < numbers.length; j++) {
				arr[i][j] = Double.valueOf(numbers[j]);
			}
		}
		try {
			Matrix toReturn = new Matrix(arr);
			return toReturn;
		}
		catch (IllegalArgumentException e) {
			throw new IllegalArgumentException("\nInvalid dimensions while creating the Matrix");
		}
    }

    @Override
    public Matrix visitVariable(MatricesParser.VariableContext ctx) {
    	System.out.println("visit variable");
    	if (variables.containsKey(ctx.VAR().getText())) {
    		return variables.get(ctx.VAR().getText());
    	}
    	else {
    		throw new NoSuchElementException("\nThere is no such variable in the HashMap");
    	}
    }

    @Override
    public Matrix visitCalculate(MatricesParser.CalculateContext ctx) {
    	System.out.println("visit calculate");
        return visit(ctx.plusOrMinus());
    }
}
