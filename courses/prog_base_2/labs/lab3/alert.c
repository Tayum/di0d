#include <stdlib.h>
#include <stdio.h>

#include "alert.h"

struct alertArr_s {
	void ** arr;
	int maxSize;
	int curSize;
};

alertArr_t * alertArr_new(int size) {
	alertArr_t * alertQueueSmp = malloc(sizeof(struct alertArr_s));
	alertQueueSmp->arr = calloc(size, sizeof(void *));
	alertQueueSmp->maxSize = size;
	alertQueueSmp->curSize = 0;
	return alertQueueSmp;
}

void alertArr_free(alertArr_t * self) {
	free(self->arr);
	free(self);
}

void alertArr_addLast(alertArr_t * self, void * element) {
	if (alertArr_isFull != YES) {
		self->arr[self->curSize] = element;
		self->curSize++;
	}
}

void * alertArr_getByInd(const alertArr_t * self, int index) {
	if (alertArr_isEmpty(self) == YES || index < 0 || index >= self->maxSize) {
		return NULL;
	}
	else {
		void * element = self->arr[index];
		return element;
	}
}

int alertArr_getSize(const alertArr_t * self) {
	return self->curSize;
}

int alertArr_isEmpty(const alertArr_t * self) {
	if (self->curSize == 0) {
		return YES;
	}
	else {
		return NO;
	}
}

int alertArr_isFull(const alertArr_t * self) {
	if (self->curSize == self->maxSize) {
		return YES;
	}
	else {
		return NO;
	}
}