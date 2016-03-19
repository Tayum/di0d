#include <stdlib.h>
#include <conio.h>
#include "lab1.h"

int main(void) {
	const int sizeTurn = 4;
	const int sizeTerm = 3;
	srand(time(NULL));

	turnSystem_t * turnSample = turn_new(sizeTurn);
	termSystem_t * termSample = term_new(sizeTerm);

	turn_fill(turnSample);
	term_fill(termSample);

	turn_rand(turnSample);
	term_from_turn(turnSample, termSample);

	interface_all(termSample);

	turn_free(turnSample);
	term_free(termSample);

	getch();
	return 0;
}

/*#include <stdlib.h>
#include <conio.h>
#include "lab1.h"

int main(void) {
	const int sizeTurn = 4;
	const int sizeTerm = 3;
	srand(time(NULL));

	turnSystem_t * turnSample = turn_new(sizeTurn);
	termSystem_t * termSample = term_new(sizeTerm);

	turn_fill(turnSample);
	term_fill(termSample);

	turn_rand(turnSample);
	term_from_turn(turnSample, termSample);

	interface_all(termSample);

	turn_free(turnSample);
	term_free(termSample);

	getch();
	return 0;
}*/

/*#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "lab1.h"


//Unit-test functions go here (in order if function name confuses you (but it shouldn't), the small description is added):

//The first function: checks if memory were allocated (for turn_new function)
static void new_void_memoryAllocatedTurn(void ** state) {
	const int sizeTurn = 4;
	turnSystem_t * turnSample = turn_new(sizeTurn);

	assert_non_null(turnSample);
	turn_free(turnSample);
}

//The second function: checks if memory were allocated (for term_new function)
static void new_void_memoryAllocatedTerm(void **state) {
	const int sizeTerm = 3;
	termSystem_t * termSample = term_new(sizeTerm);

	assert_non_null(termSample);
	term_free(termSample);
}

//The third function: checks if turnFill and termFill functions work properly
static void turnFill_termFill__void__checkCorrectFillOf_turnCounter_termName(void **state) {
	const int sizeTurn = 4;
	const int sizeTerm = 3;
	char sent[100];

	turnSystem_t * turnSample = turn_new(sizeTurn);
	termSystem_t * termSample = term_new(sizeTerm);

	turn_fill(turnSample);
	term_fill(termSample);

	assert_int_equal(0, test_turnGetCounter(turnSample, STUDENT, 2));
	char * res = test_termGetName(sent, termSample, TEACHER);
	assert_string_equal(res, "TEACHERS_TERMINAL");
	turn_free(turnSample);
	term_free(termSample);
}

//The fourth function: checks if turnRand works properly (counter increases)
static void turnRand_void_turnCounterIncreases(void **state) {
	const int sizeTurn = 4;
	int sumTurn = 0;

	turnSystem_t * turnSample = turn_new(sizeTurn);
	turn_fill(turnSample);
	turn_rand(turnSample);

	for (int i = 0; i < sizeTurn; i++) {
		for (int j = 0; j < 3; j++) {
			sumTurn = sumTurn + test_turnGetCounter(turnSample, j, sizeTurn);
		}
	}

	assert_int_not_equal(sumTurn, 0);
	turn_free(turnSample);
}

//The fifth function: checks if term_from_turn works properly (sum got from tourniquets is equal to sum transported to terminals)
static void term_from_turn__turnRand__passedInTurns_equal_passedInTerms(void **state) {
	const int sizeTurn = 4;
	const int sizeTerm = 3;
	int sumTurn = 0;
	int sumTerm = 0;

	turnSystem_t * turnSample = turn_new(sizeTurn);
	termSystem_t * termSample = term_new(sizeTerm);
	turn_fill(turnSample);
	term_fill(termSample);

	for (int i = 0; i < sizeTurn; i++) {
		for (int j = 0; j < 3; j++) {
			sumTurn = sumTurn + test_turnGetCounter(turnSample, j, i);
		}
	}
	term_from_turn(turnSample, termSample);
	for (int i = 0; i < sizeTerm; i++) {
		sumTerm = sumTerm + test_termGetCounter(termSample, i);
	}

	assert_int_equal(sumTurn, sumTerm);
	turn_free(turnSample);
	term_free(termSample);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(new_void_memoryAllocatedTurn),
		cmocka_unit_test(new_void_memoryAllocatedTerm),
		cmocka_unit_test(turnFill_termFill__void__checkCorrectFillOf_turnCounter_termName),
		cmocka_unit_test(turnRand_void_turnCounterIncreases),
		cmocka_unit_test(term_from_turn__turnRand__passedInTurns_equal_passedInTerms),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}*/