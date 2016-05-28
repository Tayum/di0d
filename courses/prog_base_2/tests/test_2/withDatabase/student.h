/* Task 1: Student */

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct student_s student_t;

student_t * student_new(void);
void student_free(student_t * self);
void student_fill(student_t * self, char * iden, char * group, int variant);

#endif // STUDENT_H_INCLUDED
