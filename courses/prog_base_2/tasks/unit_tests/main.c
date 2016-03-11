/*A description to changes made to the original code from previous hometask. Please read carefully:
In order to test my functions properly, addSent and delSent functions return values were changed
to int (from void) and their bodies were slightly changed, so they can return erCodes
(which are, by the way, described in small newly-added enum in header file),
and also getLine function was added so certain line can be received without being modified.
These small changes shouldn't cause problems, right? If they do, please, inform me and tell me what should I change.
Thank you for the attention.
*/

#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "module.h"


//Unit-test functions go here (in order if function name confuses you (but it shouldn't), the small description is added):

//The first function: checks if memory were allocated 
static void new_void_memoryAllocated(void ** state) {
	const int size = 5;
	line_t * testLine = line_new(size);
	assert_non_null(testLine);
	line_free(testLine);
}

//The second function: checks size & if line_fill/getLine works properly
static void lineFill_getSize_getLine__void__checkCorrect_size_fill_getAtIndex(void **state) {
	const int size = 5;
	char sent[100];
	line_t * lineSample = line_new(size);

	assert_int_equal(line_getSize(lineSample), size);
	line_fill(lineSample);

	char * res = line_getLine(sent, lineSample, 1);
	assert_string_equal(res, "1 sample of text here.");
	line_free(lineSample);
}

//The third function: checks if invalid indeces are handled (test reffers both to addSent and to deleteSent functions)
static void addSent_delSent__invalidInd__errorCode(void **state) {
	const int size = 5;
	line_t * lineSample = line_new(size);

	assert_int_equal(line_addSent(lineSample, 6, "I want to be added at '7' index."), ERROR);
	assert_int_equal(line_deleteSent(lineSample, 5), ERROR);
	line_free(lineSample);
}

//The fourth function: checks if addSent works properly (size-change check included)
static void addSent__newSentAtThirdInd__correctOffset_countSix(void **state) {
	const int size = 5;
	char sent[100];
	line_t * lineSample = line_new(size);

	line_fill(lineSample);

	line_addSent(lineSample, 3, "I will be added at '3' index.");
	char * res = line_getLine(sent, lineSample, 3);

	assert_string_equal(res, "I will be added at '3' index.");
	assert_int_equal(size + 1, line_getSize(lineSample));
	line_free(lineSample);
}

//The fifth function: checks if delSent works properly (size-change check included)
static void delSent__removeSentAtThirdInd__correctOffset_countFour(void **state) {
	const int size = 5;
	char sent[100];
	line_t * lineSample = line_new(size);

	line_fill(lineSample);
	char * res = line_getLine(sent, lineSample, 3);

	line_deleteSent(lineSample, 2);
	char * resSecond = line_getLine(sent, lineSample, 2);

	assert_string_equal(res, resSecond);
	assert_int_equal(size - 1, line_getSize(lineSample));
	line_free(lineSample);
}

//The sixth function: checks if longestSent works properly
static void longestSent_addNewLongestSent_longestSent(void **state) {
	const int size = 5;
	line_t * lineSample = line_new(size);
	line_fill(lineSample);

	line_addSent(lineSample, 3, "I will be the longest sentence in the world at '3' index.");
	assert_string_equal(line_LongestSent(lineSample), "I will be the longest sentence in the world at '3' index.");
	line_free(lineSample);
}

//The seventh function: checks if longestWord works properly
static void longestWord_addNewSentWithLongestWord_longestWord(void **state) {
	const int size = 5;
	char word[20];
	line_t * lineSample = line_new(size);
	line_fill(lineSample);

	line_addSent(lineSample, 1, "Not the longest sent but the longest woooooooooord.");
	char * res = line_LongestWord(word, lineSample);
	assert_string_equal(res, "woooooooooord");
	line_free(lineSample);
}


int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(new_void_memoryAllocated),
		cmocka_unit_test(lineFill_getSize_getLine__void__checkCorrect_size_fill_getAtIndex),
		cmocka_unit_test(addSent_delSent__invalidInd__errorCode),
		cmocka_unit_test(addSent__newSentAtThirdInd__correctOffset_countSix),
		cmocka_unit_test(delSent__removeSentAtThirdInd__correctOffset_countFour),
		cmocka_unit_test(longestSent_addNewLongestSent_longestSent),
		cmocka_unit_test(longestWord_addNewSentWithLongestWord_longestWord),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}