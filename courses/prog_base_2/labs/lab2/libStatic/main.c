#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

struct queue_s {
    int * queue;
    int maxSize;
    int curSize;
    int tail;
};

queue_t * queue_new(void) {
    queue_t * queueSmp = malloc(sizeof(struct queue_s));
    queueSmp->queue = calloc(QUEUE, sizeof(int));
    queueSmp->maxSize = QUEUE;
    queueSmp->curSize = 0;
    queueSmp->tail = 0;
    return queueSmp;
}

void queue_free(queue_t * self) {
    free(self->queue);
    free(self);
}

void queue_enqueue(queue_t * self, int elem) {
    if(isFull(self) != YES) {
        self->curSize++;
    }
    if(self->tail==self->maxSize) {
        self->tail = 0;
    }
    self->queue[self->tail] = elem;
    self->tail++;
}

int queue_getByInd(queue_t * self, int index) {
    if(isEmpty(self) == YES) {
        return NO;
    }
    int retEl;
    retEl = self->queue[index];
    return retEl;
}

int queue_getSize(const queue_t * self) {
    return self->curSize;
}

int queue_getTail(const queue_t * self) {
    return self->tail;
}

int isFull(const queue_t * self) {
    if(self->curSize == self->maxSize) {
        return YES;
    }
    else {
        return NO;
    }
}

int isEmpty(const queue_t * self) {
    if(self->curSize == 0) {
        return YES;
    }
    else {
        return NO;
    }
}

void queue_show(const queue_t * self) {
    if(isEmpty(self) == YES) {
        puts("The queue is empty, nothing to display!");
    }
    else {
        int day = 0;
        if(isFull(self) != YES) {
            for (int i = 0; i < self->tail; i++) {
				printf("%i: %i cm of precipitation\n", day, self->queue[i]);
				day++;
			}
        }
        else {
            int day = 0;
            for (int i = self->tail; i < queue_getSize(self); i++) {
				printf("%i: %i cm of precipitation\n", day, self->queue[i]);
				day++;
			}
			for (int i = 0; i < self->tail; i++) {
				printf("%i: %i cm of precipitation\n", day, self->queue[i]);
				day++;
			}
		}
    }
    puts("\n");
}
