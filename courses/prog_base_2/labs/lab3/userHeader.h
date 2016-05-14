/* userFunc.h DETERMINES FUNCTION FOR USER (MAIN)! 
This means this file contains ONLY the function that is required in main.c
It has been included ONLY in main.c. Other .c files contain full functional
with proper .h files to be properly connected one with another */

#ifndef USERFUNC_H_INCLUDED
#define USERFUNC_H_INCLUDED

#include "user.h"

typedef struct queue_s queue_t;
typedef struct event_s event_t;

typedef void(*alert)(user_t * receiver, event_t * event);

queue_t * queue_new(void);
void queue_free(queue_t * self);

event_t * event_new(char * description);
void event_free(event_t * self);

void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert function);
void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert function);
char * event_getDesc(event_t * self);

void event_start(event_t * firstEv, event_t * secondEv, event_t * thirdEv, queue_t * queuePtr);

#endif // USERFUNC_H_INCLUDED
