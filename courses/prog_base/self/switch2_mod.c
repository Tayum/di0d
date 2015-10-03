#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main() {
	int day = 0;
	scanf("%d", &day);
	switch ((day-1) % 7) {
	case 0:
		printf("WEDNESDAY") ; break;
	case 1:
		printf("THURSDAY"); break;
	case 2:
		printf("FRIDAY"); break;
	case 3:
		printf("SATURDAY"); break;
	case 4:
		printf("SUNDAY"); break;
	case 5:
		printf("MONDAY"); break;
	case 6:
		printf("TUESDAY"); break;
	default:
		return 1;
	}
	return 0;
}