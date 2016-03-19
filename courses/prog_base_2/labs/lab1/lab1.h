#ifndef LAB1_H_INCLUDED
#define LAB1_H_INCLUDED

#define HUM 25

enum ID {
	STUFF,		//FIRST TERMINAL RECEIVES ONLY STUFF PASSED
	TEACHER,	//SECOND TERMINAL RECEIVES ONLY TEACHERS PASSED
	STUDENT		//THIRD TERMINAL RECEIVES ONLY STUDENTS PASSED
};

typedef struct turnSystem_s turnSystem_t;
typedef struct turn_s turn_t;
typedef struct termSystem_s termSystem_t;
typedef struct term_s term_t;

turnSystem_t * turn_new(int size);
void turn_fill(turnSystem_t * self);
void turn_rand(turnSystem_t * self);
void turn_free(turnSystem_t * self);

termSystem_t * term_new(int size);
void term_fill(termSystem_t * self);
void term_from_turn(const turnSystem_t * selfTurn, termSystem_t * selfTerm);
void term_print(const termSystem_t * self);
void term_free(termSystem_t * self);

void interface_chngCurPos(int x, int y);
void interface_borders(void);
void interface_all(const termSystem_t * self);

int test_turnGetCounter(const turnSystem_t * self, int info, int index);
int test_termGetCounter(const termSystem_t * self, int index);
char * test_termGetName(char * resultStr, const termSystem_t * self, int index);

#endif //LAB1_H_INCLUDED