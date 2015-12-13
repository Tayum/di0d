#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#define STUDENT 100
#define GROUP 3
#define LESSON 5

struct Lessons {
	char lessonName[30];
	int mark;
};

struct Group {
	char groupName[20];
	struct Lessons thyLessons[LESSON];
} Group_list[GROUP];

struct Student {
	char name[50];
	char surname[50];
	int age;
	struct Group thyGroup;
	char kick;
	char sShip[15];
} Student_list[STUDENT];

int fileLength(const char * pread);
void initList(const char * pread);
void initTimetable(const char * pread);
void initMarks(const char * pread);
int choice(void);
int findSlot(void);
void addStudent(void);
void deleteStudent(void);
void showList(void);
void showTimetable(void);
void showMarks(void);
void changeMark(void);
void showStatistics(void);
void saveFile(const char * pwrite, const char * pwrite2);

int main(void) {
	char input;
	srand(time(NULL));
	initList("students.txt"); /* Initialization of students structure array */
	initTimetable("timetable.txt"); /* Initialization of lessons structure array */
	initMarks("marks.txt"); /* Initialization of marks structure array */
	while (1) {
		system("cls");
		input = choice();
		switch (input) {
		case 1:
			addStudent();
			break;
		case 2:
			deleteStudent();
			break;
		case 3:
			showList();
			getch();
			break;
		case 4:
			showTimetable();
			getch();
			break;
		case 5:
			showMarks();
			getch();
			break;
		case 6:
			showStatistics();
			getch();
			break;
		case 7:
			changeMark();
			break;
		case 8:
			saveFile("students.txt", "marks.txt");
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

/* Counts amount of lines in file */
int fileLength(const char * pread) {
	int c;
	int lines = 0;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	do {
		c = fgetc(fr);
		if (c == '\n') {
			lines++;
		}
	} while (c != EOF);
	fclose(fr);
	return lines;
}

/* Initialization of list
(If "name" field is empty, then it is assumed that this element of structure array is not used) */
void initList(const char * pread) {
	int i;
	int lines;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	char clip[100];
	for (i = 0; i < STUDENT; i++) {
		Student_list[i].name[0] = '\0';
	}
	lines = fileLength("students.txt");
	for (i = 0; i < lines; i++) {
		fgets(clip, 100, fr);
		sscanf(clip, "%s %s %i %s %c %s", &Student_list[i].name, &Student_list[i].surname, &Student_list[i].age, &Student_list[i].thyGroup.groupName, &Student_list[i].kick, &Student_list[i].sShip);
	}
	fclose(fr);
}

/* Initialization of timetable
(If "lessonName" field is empty, then it is assumed that this element of stucture array is not used) */
void initTimetable(const char * pread) {
	int i, j;
	char clip[100];
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	for (i = 0; i < GROUP; i++) {
		fgets(clip, 100, fr);
		sscanf(clip, "%s %s %s %s %s", &Group_list[i].thyLessons[0].lessonName, &Group_list[i].thyLessons[1].lessonName, &Group_list[i].thyLessons[2].lessonName, &Group_list[i].thyLessons[3].lessonName, &Group_list[i].thyLessons[4].lessonName);
	}
	fclose(fr);
}

/* Initialization of marks */
void initMarks(const char * pread) {
	int i, j;
	char clip[100];
	int lines;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	lines = fileLength("marks.txt");
	for (i = 0; i < lines; i++) {
		fgets(clip, 100, fr);
		sscanf(clip, "%i %i %i %i %i", &Student_list[i].thyGroup.thyLessons[0].mark, &Student_list[i].thyGroup.thyLessons[1].mark, &Student_list[i].thyGroup.thyLessons[2].mark, &Student_list[i].thyGroup.thyLessons[3].mark, &Student_list[i].thyGroup.thyLessons[4].mark);
	}
	fclose(fr);
}

/* Getting the char */
int choice(void) {
	char input[100];
	int number;
	printf("1. Add student\n");
	printf("2. Delete student\n");
	printf("3. Show list of students\n");
	printf("4. Show the timetable\n");
	printf("5. Show the marks of students\n");
	printf("6. Show general student statistics\n");
	printf("7. Change student's mark\n");
	printf("8. Save structure and exit\n");
	do {
		printf("\nEnter the number of option you want to choose: ");
		gets(input);
		number = atoi(input);
	} while (number < 0 || number > 8);
	return number;
}

/* Searching for the free structure */
int findSlot(void) {
	int i;
	for (i = 0; Student_list[i].name[0] && i < STUDENT; i++);
	if (i == STUDENT) {
		return -1; /* No free structures */
	}
	return i;
}

/* Adding new student */
void addStudent(void) {
	int i;
	int slot;
	char input[100];
	char choice;
	slot = findSlot();
	if (slot == -1) {
		printf("\nThe list is full");
		return;
	}
	printf("Enter name: \n");
	gets(Student_list[slot].name);
	printf("Enter surname: \n");
	gets(Student_list[slot].surname);
	printf("Enter age: \n");
	gets(input);
	Student_list[slot].age = atoi(input);
	printf("Choose the group {1 is KM-51, 2 is KM-52, 3 is KM-53}: \n");
	do {
		choice = getch();
	} while (choice != '1' && choice != '2' && choice != '3');
	switch (choice) {
	case '1':
		strcpy(Student_list[slot].thyGroup.groupName, "KM-51");
		break;
	case '2':
		strcpy(Student_list[slot].thyGroup.groupName, "KM-52");
		break;
	case '3':
		strcpy(Student_list[slot].thyGroup.groupName, "KM-53");
		break;
	}
	printf("Choose, whether he is gonna be kicked or not {+/-}: \n");
	do {
		Student_list[slot].kick = getch();
	} while (Student_list[slot].kick != '+' && Student_list[slot].kick != '-');
	printf("Choose, what grade of scholarship will he have {1-None,2-Basic,3-Advanced}: \n");
	do {
		choice = getch();
	} while (choice != '1' && choice != '2' && choice != '3');
	switch (choice) {
	case '1':
		strcpy(Student_list[slot].sShip, "None");
		break;
	case '2':
		strcpy(Student_list[slot].sShip, "Basic");
		break;
	case '3':
		strcpy(Student_list[slot].sShip, "Advanced");
		break;
	}
	for (i = 0; i < LESSON; i++) {
		Student_list[slot].thyGroup.thyLessons[i].mark = rand() % 100;
	}
}

/* Deleting the student */
void deleteStudent(void) {
	int slot;
	char input[100];
	printf("Enter the number of student: ");
	gets(input);
	slot = atoi(input);
	if (slot >= 0 && slot < STUDENT) {
		Student_list[slot].name[0] = '\0';
	}
}

/* Showing list of all students */
void showList(void) {
	int i;
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0') {
			printf("%i. Name: %s\n", i, Student_list[i].name);
			printf("Surname: %s\n", Student_list[i].surname);
			printf("Age: %i\n", Student_list[i].age);
			printf("Group: %s\n", Student_list[i].thyGroup.groupName);
			printf("Kick: %c\n", Student_list[i].kick);
			printf("Scholarship: %s\n\n", Student_list[i].sShip);
		}
	}
	puts("\n");
}

/* Showing timetable of group */
void showTimetable(void) {
	int i;
	printf("\nKM-51:\n");
	for (i = 0; i < LESSON; i++) {
		printf("%i) %s\n", i, Group_list[0].thyLessons[i].lessonName);
	}
	printf("KM-52:\n");
	for (i = 0; i < LESSON; i++) {
		printf("%i) %s\n", i, Group_list[1].thyLessons[i].lessonName);
	}
	printf("KM-53:\n");
	for (i = 0; i < LESSON; i++) {
		printf("%i) %s\n", i, Group_list[2].thyLessons[i].lessonName);
	}
}

/* Showing marks of students */
void showMarks(void) {
	int i, j;
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0') {
			printf("%i. %s %s (%s):\n", i, Student_list[i].name, Student_list[i].surname, Student_list[i].thyGroup.groupName);
			if (strcmp(Student_list[i].thyGroup.groupName, "KM-51") == 0) {
				for (j = 0; j < LESSON; j++) {
					printf("%i) %s: %i\n", j, Group_list[0].thyLessons[j].lessonName, Student_list[i].thyGroup.thyLessons[j].mark);
				}
				puts("");
			}
			else if (strcmp(Student_list[i].thyGroup.groupName, "KM-52") == 0) {
				for (j = 0; j < LESSON; j++) {
					printf("%i) %s: %i\n", j, Group_list[1].thyLessons[j].lessonName, Student_list[i].thyGroup.thyLessons[j].mark);
				}
				puts("");
			}
			else if (strcmp(Student_list[i].thyGroup.groupName, "KM-53") == 0) {
				for (j = 0; j < LESSON; j++) {
					printf("%i) %s: %i\n", j, Group_list[2].thyLessons[j].lessonName, Student_list[i].thyGroup.thyLessons[j].mark);
				}
				puts("");
			}
		}
	}
}

/* Changes mark of the student */
void changeMark(void) {
	showMarks();
	int index;
	char clip[100];
	char choice;
	int mark;
	printf("Enter the index of the student:\n");
	gets(clip);
	index = atoi(clip);
	if (index >= 0 && index < STUDENT && Student_list[index].name[0] != '\0') {
		printf("Enter the number of lesson you want to change mark of {0/1/2/3/4}:\n");
		do {
			choice = getch();
		} while (choice != '0' && choice != '1' && choice != '2' && choice != '3' && choice != '4');
		printf("%i\n", choice - '0');
		printf("Enter the mark directly:\n");
		gets(clip);
		mark = atoi(clip);
		Student_list[index].thyGroup.thyLessons[choice - '0'].mark = mark;
	}
}

/* Shows general statistics */
void showStatistics(void) {
	int i;
	printf("Students, who is about to be kicked:\n");
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0' && Student_list[i].kick == '+') {
			printf("%s %s\n", Student_list[i].name, Student_list[i].surname);
		}
	}
	puts("");
	printf("Students that don't have scholarship:\n");
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0' && strcmp(Student_list[i].sShip, "None") == 0) {
			printf("%s %s\n", Student_list[i].name, Student_list[i].surname);
		}
	}
	puts("");
	printf("Students that have basic level of scholarship:\n");
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0' && strcmp(Student_list[i].sShip, "Basic") == 0) {
			printf("%s %s\n", Student_list[i].name, Student_list[i].surname);
		}
	}
	puts("");
	printf("Students the have advanced level of scholarship:\n");
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0' && strcmp(Student_list[i].sShip, "Advanced") == 0) {
			printf("%s %s\n", Student_list[i].name, Student_list[i].surname);
		}
	}
}

/* Saving the data to file */
void saveFile(const char * pwrite, const char * pwrite2) {
	int i;
	FILE * fw = fopen(pwrite, "w");
	FILE * fw2 = fopen(pwrite2, "w");
	if ((fw = fopen(pwrite, "w")) == NULL || (fw2 = fopen(pwrite2, "w")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	for (i = 0; i < STUDENT; i++) {
		if (Student_list[i].name[0] != '\0') {
			fprintf(fw, "%s %s %i %s %c %s\n", Student_list[i].name, Student_list[i].surname, Student_list[i].age, Student_list[i].thyGroup.groupName, Student_list[i].kick, Student_list[i].sShip);
			fprintf(fw2, "%i %i %i %i %i\n", Student_list[i].thyGroup.thyLessons[0].mark, Student_list[i].thyGroup.thyLessons[1].mark, Student_list[i].thyGroup.thyLessons[2].mark, Student_list[i].thyGroup.thyLessons[3].mark, Student_list[i].thyGroup.thyLessons[4].mark);
		}
	}
	fclose(fw);
	fclose(fw2);
}