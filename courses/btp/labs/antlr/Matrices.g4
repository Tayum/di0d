/**
 * Define a grammar called Matrices
 */
grammar Matrices;

//NL: '\n';
WS: [ \n\t\r]+ -> skip;

VAR: [a-zA-Z]+;

NUMBER: '-'?([0-9]+ | [0-9]+'.'[0-9]+);
VECTOR: '['NUMBER(','NUMBER)*']';
MATRIX: '['VECTOR(';'VECTOR)*']';

PLUS: '+';
EQUAL: '=';
MINUS: '-';
MULT: '*';
TRANS: '^T';
RNK: '^R';
LB: '(';
RB: ')';

root: 
	input EOF # RootRule
	;

input:
	setVar		  # ToSetVar  // setVar NL input
    | plusOrMinus # Calculate // | plusOrMinus NL     (OR older) | plusOrMinus NL? EOF
    ;

setVar:
    VAR EQUAL input # SetVariable
    ;


plusOrMinus:
    plusOrMinus PLUS mult    # Plus
    | plusOrMinus MINUS mult # Minus
    | mult                   # ToMultiplication
    ;

mult:
	mult MULT NUMBER   # MultiplicationByNumber
	| NUMBER MULT mult # MultiplicationByNumber
	| mult MULT rnk	   # Multiplication
    | rnk         	   # ToRank
    ;

rnk:
    trans (RNK)? # Rank
    ;

trans:
	atom (TRANS)? # Transpose
	;

atom:
	MATRIX				# Matrix
    | VAR               # Variable
    | LB plusOrMinus RB # Braces
    ;