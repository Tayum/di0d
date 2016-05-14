#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "alert.h"
#include "event.h"

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
// this function is HIDDEN FROM USER, so ITS STATIC!
static void event_trigger(event_t * self) {
	event_t * event = self;
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		alert_t * alert = (alert_t *)alertArr_getByInd(self->alert_array, i);
		alert->func(alert->receiver, self);
	}
}

// function that calls event_trigger function if (for first event)
// the condition (for first event) is satisfied.
// It also returns some of DEFINEs (from queue.h) to handle the
// behaviour of the program in function below (check event_start)
//
// this function is HIDDEN FROM USER, so ITS STATIC!
static int event_firstEvent(event_t * self, queue_t * queuePtr) {
	if (queue_firstEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_firstEvent(queuePtr) == NO) {
		return NO;
	}
	else {
		puts("\n==========FIRST EVENT TAKES PLACE!!!==========\n");
		event_trigger(self);
	}
}

// function that calls event_trigger function if (for second event)
// the condition (for second event) is satisfied.
// It also returns some of DEFINEs (from queue.h) to handle the
// behaviour of the program in function below (check event_start)
//
// this function is HIDDEN FROM USER, so ITS STATIC!
static int event_secondEvent(event_t * self, queue_t * queuePtr) {
	if (queue_secondEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_secondEvent(queuePtr) == NO) {
		return NO;
	}
	else {
		puts("\n==========SECOND EVENT TAKES PLACE!!!==========\n");
		event_trigger(self);
	}
}

// function that calls event_trigger function (for third event)
// if the condition (for third event) is satisfied.
// It also returns some of DEFINEs (from queue.h) to handle the
// behaviour of the program in function below (check event_start)
//
// this function is HIDDEN FROM USER, so ITS STATIC!
static int event_thirdEvent(event_t * self, queue_t * queuePtr) {
	if (queue_thirdEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_thirdEvent(queuePtr) == NO) {
		return NO;
	}
	else {
		puts("\n==========THIRD EVENT TAKES PLACE!!!==========\n");
		event_trigger(self);
	}
}

// MAIN function of our program that is DEFINED IN userFunc.h (and therefore in main.c)
// Controls the behaviour (printing to console, Sleep() and other) of main cycle of our program
// The cycle is next: enqueue, checking on first, second, third event and go on again
//
// if the condition for some event is fulfilled - the event_trigger from corresponding function
// (see 3 functions above) is called.
// for other occasions (for example, when there is no enough data or the condition is NOT satisfied) -
// this function prints the appropriate message.
void event_start(event_t * firstEv, event_t * secondEv, event_t * thirdEv, queue_t * queuePtr) {
	puts("\n====================NEW MEASURMENT====================\n");
	queue_enqueueRand(queuePtr);
	int check;

	Sleep(1000);
	check = event_firstEvent(firstEv, queuePtr);
	if (check == DATA || check == NO) {
		puts("\nFirst event:\n");

		if (check == DATA) {
			puts("NO DATA FOR FIRST EVENT!");
		}
		else if (check == NO) {
			puts("Nothing special in first event...");
		}
	}

	Sleep(1000);
	check = event_secondEvent(secondEv, queuePtr);
	if (check == DATA || check == NO) {
		puts("\nSecond event:\n");

		if (check == DATA) {
			puts("NO DATA FOR SECOND EVENT!");
		}
		else if (check == NO) {
			puts("Nothing special in second event...");
		}
	}

	Sleep(1000);
	check = event_thirdEvent(thirdEv, queuePtr);
	if (check == DATA || check == NO) {
		puts("\nThird event:\n");

		if (check == DATA) {
			puts("NO DATA FOR THIRD EVENT!");
		}
		else if (check == NO) {
			puts("Nothing special in third event...");
		}
	}

	Sleep(1000);
	puts("\n\n");
}