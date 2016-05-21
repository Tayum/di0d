/* To add the libcmocka.dll.a  cmocka library, go to
Project -> Properties -> Linker -> Input -> Additional Independencies
(Proekt -> Svoistva -> Komponovschik -> Vvod -> Dopolnitelnie zavisimosti)
and add your path instead of this path:
C:\Program Files (x86)\cmocka\lib\libcmocka.dll.a 

To add the cmocka.h cmocka header file, go to
Project -> Properties -> C/C++ -> General -> Additional Include Directories
(Proekt -> Svoistva -> C/C++ -> Obshie -> Dopolnitelnie katalogi vkluchaemuh failov)
and add your path instead of this path:
C:\Program Files (x86)\cmocka\include
*/

// add callback_function
// printf("Current local time and date: %s", asctime(currentTime));

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "chat.h"
#include "cmockaTest.h"

int main(void) {
	// =====conducting the unit tests=====
	cmockaTest();
	printf("\nPress ANY KEY to proceed to actually program...");
	getch();
	system("cls");
	// end of conducting the unit tests



	// end of program
	printf("\n\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}