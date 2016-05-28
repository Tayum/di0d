#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "studentStruct.h"

student_t * student_new(void) {
	student_t * studentSmp = malloc(sizeof(struct student_s));
	studentSmp->student = "NoNameSurname";
	studentSmp->group = "No group";
	studentSmp->variant = 0;
}

void student_free(student_t * self) {
	free(self);
}

void student_fill(student_t * self, char * iden, char * group, int variant) {
	self->student = iden;
	self->group = group;
	self->variant = variant;
}