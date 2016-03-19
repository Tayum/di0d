#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "lab1.h"

COORD CurrPos;
HANDLE consHndlr;

//TOURNIQUETS FUNCTIONS GO HERE
struct turn_s {
	int passStud;
	int passTeach;
	int passStuff;
};

struct turnSystem_s {
	int size;
	turn_t * thyTurns;
};

turnSystem_t * turn_new(int size) {
	turnSystem_t * turnSample = malloc(sizeof(struct turnSystem_s));
	turnSample->thyTurns = calloc(size, sizeof(turn_t));
	turnSample->size = size;
	return turnSample;
}

void turn_free(turnSystem_t * self) {
	free(self->thyTurns);
	free(self);
}

void turn_fill(turnSystem_t * self) {
	for (int i = 0; i < self->size; i++) {
		self->thyTurns[i].passStud = 0;
		self->thyTurns[i].passTeach = 0;
		self->thyTurns[i].passStuff = 0;
	}
}

void turn_rand(turnSystem_t * self) {
	int idT;
	int idH;
	for (int i = 0; i < HUM; i++) {
		idT = rand() % self->size;
		idH = rand() % 3;
		if (idH == STUFF) {
			self->thyTurns[idT].passStuff++;
		}
		else if (idH == TEACHER) {
			self->thyTurns[idT].passTeach++;
		}
		else if (idH == STUDENT) {
			self->thyTurns[idT].passStud++;
		}
	}
}

//TERMINALS FUNCTIONS GO HERE
struct termSystem_s {
	int size;
	term_t * thyTerms;
};

struct term_s {
	char name[30];
	int passed;
};

termSystem_t * term_new(int size) {
	termSystem_t * termSample = malloc(sizeof(struct termSystem_s));
	termSample->thyTerms = calloc(size, sizeof(term_t));
	termSample->size = size;
	return termSample;
}

void term_free(termSystem_t * self) {
	free(self->thyTerms);
	free(self);
}

void term_fill(termSystem_t * self) {
	if (self->size >= 1) {
		if (self->size >= 2) {
			if (self->size >= 3) {
				strcpy(self->thyTerms[0].name, "STUFF_TERMINAL");
				strcpy(self->thyTerms[1].name, "TEACHERS_TERMINAL");
				strcpy(self->thyTerms[2].name, "STUDENTS_TERMINAL");
			}
			else {
				strcpy(self->thyTerms[0].name, "STUFF_TERMINAL");
				strcpy(self->thyTerms[1].name, "TEACHERS_TERMINAL");
			}
		}
		else {
			strcpy(self->thyTerms[0].name, "STUFF_TERMINAL");
		}
	}
	for (int i = 0; i < self->size; i++) {
		self->thyTerms[i].passed = 0;
	}
}

void term_from_turn(const turnSystem_t * selfTurn, termSystem_t * selfTerm) {
	for (int i = 0; i < selfTurn->size; i++) {
		for (int j = 0; j < selfTerm->size; j++) {
			if (strcmp(selfTerm->thyTerms[j].name, "STUFF_TERMINAL") == 0) {
				selfTerm->thyTerms[j].passed = selfTerm->thyTerms[j].passed + selfTurn->thyTurns[i].passStuff;
			}
			else if (strcmp(selfTerm->thyTerms[j].name, "TEACHERS_TERMINAL") == 0) {
				selfTerm->thyTerms[j].passed = selfTerm->thyTerms[j].passed + selfTurn->thyTurns[i].passTeach;
			}
			else if (strcmp(selfTerm->thyTerms[j].name, "STUDENTS_TERMINAL") == 0) {
				selfTerm->thyTerms[j].passed = selfTerm->thyTerms[j].passed + selfTurn->thyTurns[i].passStud;
			}
		}
	}
}

void term_print(const termSystem_t * self) {
	for (int i = 0; i < self->size; i++) {
		if (strcmp(self->thyTerms[i].name, "STUFF_TERMINAL") == 0) {
			interface_chngCurPos(0, 0);
			printf("%s statistics:", self->thyTerms[i].name);
			interface_chngCurPos(0, 1);
			printf("STUFF passed: %i", self->thyTerms[i].passed);
		}
		else if (strcmp(self->thyTerms[i].name, "TEACHERS_TERMINAL") == 0) {
			interface_chngCurPos(42, 0);
			printf("%s statistics:", self->thyTerms[i].name);
			interface_chngCurPos(42, 1);
			printf("TEACHERS passed: %i", self->thyTerms[i].passed);
		}
		else if (strcmp(self->thyTerms[i].name, "STUDENTS_TERMINAL") == 0) {
			interface_chngCurPos(26, 11);
			printf("%s statistics:", self->thyTerms[i].name);
			interface_chngCurPos(26, 12);
			printf("STUDENTS passed: %i", self->thyTerms[i].passed);
		}
	}
}

//ADDITIONAL INTERFACE FUNCTIONS GO HERE
void interface_chngCurPos(int x, int y) {
	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	CurrPos.X = x;
	CurrPos.Y = y;
	SetConsoleCursorPosition(consHndlr, CurrPos);
}

void interface_borders(void) {
	for (int i = 0; i < 10; i++) {
		interface_chngCurPos(40, i);
		puts("|");
	}
	interface_chngCurPos(0, 10);
	for (int i = 0; i < 80; i++) {
		printf("-");
	}
	interface_chngCurPos(0, 20);
	for (int i = 0; i < 80; i++) {
		printf("-");
	}
}

void interface_all(const termSystem_t * self) {
	interface_borders();
	term_print(self);
}

//ADDITIONAL FUNCTIONS REQUIRED FOR TESTING GO HERE
int test_turnGetCounter(const turnSystem_t * self, int info, int index) {
	if ((info != STUFF && info != TEACHER && info != STUDENT) || (index < 0 || index>= self->size)) {
		return -1;
	}
	else if (info == STUFF) {
		return self->thyTurns[index].passStuff;
	}
	else if (info == TEACHER) {
		return self->thyTurns[index].passTeach;
	}
	else if (info == STUDENT) {
		return self->thyTurns[index].passStud;
	}
}

int test_termGetCounter(const termSystem_t * self,int index) {
	if (index < 0 || index >= self->size) {
		return -1;
	}
	else {
		return self->thyTerms[index].passed;
	}
}

char * test_termGetName(char * resultStr, const termSystem_t * self, int index) {
	if (index < 0 || index >= self->size) {
		strcpy(resultStr, "-1");
		return resultStr;
	}
	else {
		strcpy(resultStr, self->thyTerms[index].name);
		return resultStr;
	}
}