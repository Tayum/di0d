#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define QUEUE 14
#define YES 1
#define NO -1 //also as ERROR

typedef struct queue_s queue_t;

queue_t * queue_new(void);
void queue_free(queue_t * self);

void queue_enqueue(queue_t * self, int element);
int queue_getByInd(queue_t * self, int index);

int queue_getSize(const queue_t * self);
int queue_getTail(const queue_t * self);
int isFull(const queue_t * self);
int isEmpty(const queue_t * self);

void queue_show(const queue_t * self);

#endif //QUEUE_H_INCLUDED
