#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "queue.h"

struct queue_s {
	float * queue;
	int maxSize;
	int curSize;
	int tail;
};

queue_t * queue_new(void) {
	queue_t * queueSmp = malloc(sizeof(struct queue_s));
	queueSmp->queue = calloc(QUEUE_MAXSIZE, sizeof(float));
	queueSmp->maxSize = QUEUE_MAXSIZE;
	queueSmp->curSize = 0;
	queueSmp->tail = 0;
	return queueSmp;
}

void queue_free(queue_t * self) {
	free(self->queue);
	free(self);
}

// returns enqueued element to have opporunity to check in unit_tests
float queue_enqueueRand(queue_t * self) {
	if (queue_isFull(self) != YES) {
		self->curSize++;
	}
	if (self->tail == self->maxSize) {
		self->tail = 0;
	}
	float elem = (float)pow(-1, rand()) * ((float)((double)rand() / (double)(RAND_MAX)) * MAX_VALUE);
	self->queue[self->tail] = elem;
	self->tail++;
	return elem;
}

float queue_getByInd(const queue_t * self, int index) {
	if (queue_isEmpty(self) == YES || index < 0 || index >= self->curSize) {
		return EMPTY_ELEM;
	}
	float retEl;
	retEl = self->queue[index];
	return retEl;
}

int queue_getSize(const queue_t * self) {
	return self->curSize;
}

int queue_isFull(const queue_t * self) {
	if (self->curSize == self->maxSize) {
		return YES;
	}
	else {
		return NO;
	}
}

int queue_isEmpty(const queue_t * self) {
	if (self->curSize == 0) {
		return YES;
	}
	else {
		return NO;
	}
}

// checking if condition for first event was fulfilled
int queue_firstEvent(const queue_t * self) {
	if (queue_isFull(self) != YES) {
		return DATA;
	}
	else {
		float sum = 0;
		for (int i = 0; i < queue_getSize(self); i++) {
			sum += self->queue[i];
		}
		sum /= queue_getSize(self);
		sum = fabs(sum);
		if (sum <= 1) {
			return YES;
		}
		else {
			return NO;
		}
	}
}

// checking if condition for second event was fulfilled
int queue_secondEvent(const queue_t * self) {
	if (queue_getSize(self) < 5) {
		return DATA;
	}
	else {
		float sum = 0;
		if (self->tail >= 5) {
			for (int i = self->tail - 5; i < self->tail; i++) {
				sum += self->queue[i];
			}
		}
		else {
			for (int i = self->tail - 1; i >= 0; i--) {
				sum += self->queue[i];
			}
			for (int i = queue_getSize(self) - (5 - self->tail); i < queue_getSize(self); i++) {
				sum += self->queue[i];
			}
		}
		sum = fabs(sum);
		if (sum > 5) {
			return YES;
		}
		else {
			return NO;
		}
	}
}

// checking if condition for third event was fulfilled
int queue_thirdEvent(const queue_t * self) {
	if (queue_getSize(self) < 5) {
		return DATA;
	}
	else {
		float sum = 0;
		if (self->tail >= 5) {
			for (int i = self->tail - 5; i < self->tail; i++) {
				sum += self->queue[i];
			}
		}
		else {
			for (int i = self->tail - 1; i >= 0; i--) {
				sum += self->queue[i];
			}
			for (int i = queue_getSize(self) - (5 - self->tail); i < queue_getSize(self); i++) {
				sum += self->queue[i];
			}
		}
		sum = fabs(sum);
		if (sum > 10) {
			return YES;
		}
		else {
			return NO;
		}
	}
}