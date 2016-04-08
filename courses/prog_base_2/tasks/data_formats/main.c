#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "investors.h"

#define INVESTORS 4

int main(void) {
	investor_t * investorsArr[INVESTORS];
	// Create samples
	for (int i = 0; i < INVESTORS; i++) {
		investorsArr[i] = investor_new();
	}
	// Parse investors from file
	investor_ParseXML(investorsArr, "investors.xml");
	// Print investor
	for (int i = 0; i < INVESTORS; i++) {
		investor_print(investorsArr[i]);
	}
	// Free investor
	for (int i = 0; i < INVESTORS; i++) {
		investor_delete(investorsArr[i]);
	}
	// End of program
	puts("\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}