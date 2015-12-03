#include <stdio.h>
#include <stdlib.h>

struct Patient {
	char name [100];
	int age;
	char diagnose [100];
};

void print(struct Patient * pVar);
int count(int size, struct Patient pPatients[]);
void change(struct Patient * pVar, const char * newValue);

int main(void) {
	struct Patient pPatients[] = { {"James Hetfield",52,"brain METAL"}, {"David Draiman",18,"Locked in ASYLUM"}, {"Fred Durst",16,"Lives in such a lonely world"}, {"Angus Young",60,"Brain ROCK"},{"Darren Korb",12,"Bright imagination"} };
	int size = 5;
	int i;
	char nums[4][100];
	int index;
	char answer = 0;
	puts("\t\tBONJOUR AND WELCOME TO THE ROCK CLINICS!!!\n");
	for (i = 0; i < 5; i++) {
		printf("%i. ", i+1);
		print(&pPatients[i]);
	}
	puts("");
	printf("Number of immature guys: %i\n", count(size, pPatients));
	while (1) {
		printf("\nEnter the index of the guy whose diagnose you wanna change: ");
		gets(nums[0]);
		index = atoi(nums[0]);
		if (index < 1 || index > size) {
			printf("Invalid index, try again!\n");
			continue;
		}
		printf("Now enter new diagnose: ");
		gets(nums[1]);
		puts("");
		change(&pPatients[index-1], nums[1]);
		for (i = 0; i < 5; i++) {
			printf("%i. ", i + 1);
			print(&pPatients[i]);
		}
		printf("Do you want to change another diagnose? {y/n}\n");
		do {
			answer = getch();
		} while (answer != 'n' && answer != 'y');
		switch (answer) {
		case 'y':
			continue;
		case 'n':
			break;
		}
		break;
	}
	printf("Press any key to continue...");
	getch();
	return 0;
}

void print(struct Patient * pVar) {
	printf("Name: %s\n", pVar->name);
	printf("Age: %i\n", pVar->age);
	printf("Diagnose: %s\n", pVar->diagnose);
	puts("");
}

int count(int size, struct Patient pPatients[]) {
	int minor=0;
	int i;
	for (i = 0; i < size; i++) {
		if (pPatients[i].age < 18) {
			minor++;
		}
	}
	return minor;
}

void change(struct Patient * pVar, const char * newValue) {
	strcpy(pVar->diagnose, newValue);
}