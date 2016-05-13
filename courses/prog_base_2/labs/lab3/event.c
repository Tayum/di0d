#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "user.h"
#include "alert.h"

// max amount of users that are able to be subscribed to the same event at the same time
#define USERS_MAXSIZE 100

// struct that has receiver (the person who subscribed to some event) field - to know
// who to notify, and the func with alert type - the callback function that user wants to REACT WITH.
// It is incapsulated because it's not existing by itself, but only with
// event struct (see below).
struct alert_s {
	user_t * receiver;
	alert func;
};

typedef struct alert_s alert_t;

// event struct. It has desc field - the field that describes the essence of the event
// and also has alert_t array. It's array of alerts: users, who subscribed to this event
// and their reactions on the event if it will occur.
struct event_s {
	char desc[100];
	alert_t * alert_array;
};

event_t * event_new(char * description) {
	event_t * eventSmp = malloc(sizeof(struct event_s));
	strcpy(eventSmp->desc, description);
	eventSmp->alert_array = alertArr_new(USERS_MAXSIZE);
	return eventSmp;
}

void event_free(event_t * self) {
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		free(alertArr_getByInd(self->alert_array, i));
	}
	alertArr_free(self->alert_array);
	free(self);
}

char * event_getDesc(event_t * self) {
	char * desc = malloc((strlen(self->desc) + 1) * sizeof(char));
	strcpy(desc, self->desc);
	return desc;
}

// function that subscribes ONE user with his alert function to the event
void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert function) {
	alert_t * alertSmp = malloc(sizeof(struct alert_s));
	alertSmp->receiver = userPtr;
	alertSmp->func = function;
	alertArr_addLast(evPtr->alert_array, alertSmp);
}

// function that subscribes array of users with their COMMON FUNCTION
// (COMMON means that it should be THE SAME for all users in array!)
void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert function) {
	for (int i = 0; i < userSize; i++) {
		event_addAlertSingle(userArray[i], evPtr, function);
	}
}

// function that triggers the event. Each subscriber (user) from alert_array (user_t * receiver)
// is being notified with the special message: "desc" in event_s struct
// and he reacts on the event trigger with his alert function from alert_array (alert func)
void event_trigger(event_t * self) {
	event_t * event = self;
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		alert_t * alert = (alert_t *)alertArr_getByInd(self->alert_array, i);
		alert->func(alert->receiver, self);
	}
}

