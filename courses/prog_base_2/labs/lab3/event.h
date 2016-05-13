/* event.h DESCRIBES THE struct event_s, CALLBACK FUNCTION alert AND THE METHODS TO BOUND alert WITH struct event_s
(check event.c to know more) */

#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "user.h"

typedef struct event_s event_t;

typedef void (*alert)(user_t * receiver, event_t * event);

event_t * event_new(char * description);
void event_free(event_t * self);

char * event_getDesc(event_t * self);
void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert function);
void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert function);
void event_trigger(event_t * self);

#endif // EVENT_H_INCLUDED