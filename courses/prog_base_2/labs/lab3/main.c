#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "queue.h"
#include "user.h"
#include "event.h"
#include "cmockaTest.h"

// first variation of callback function for ruslan user as the master user
void alert_master(user_t * receiver, event_t * event);
// second variation of callback function for other users (including ruslan)
void alert_common(user_t * receiver, event_t * event);

int main(void) {
	srand(time(NULL));

	// =====conducting the unit tests=====
	cmockaTest();
	puts("\nPress ANY KEY to proceed to actually program...");
	getch();
	system("cls");

	// =====main program=====
	// initialising the main queue with measurements
	queue_t * msrmQueue = queue_new();
	// initialising users (and their array)
	user_t * ruslan = user_new("Ruslan");
	user_t * alpha = user_new("Alpha");
	user_t * bravo = user_new("Bravo");
	user_t * charlie = user_new("Charlie");
	user_t * delta = user_new("Delta");
	user_t * userArr[] = { ruslan, alpha, bravo, charlie, delta };
	int userArrSize = sizeof(userArr) / sizeof(userArr[0]);
	// initialising events: 3 types (according to variant)
	event_t * firstEvent = event_new("According to 10 measurements, device is behaving perfectly.");
	event_t * secondEvent = event_new("According to last 5 measurements, device is behaving strangely.");
	event_t * thirdEvent = event_new("HITLER KAPUT! THE DEVICE IS RUNNING DOWN!");
	// subscribing user ruslan (for first two events) with alert_master callback function
	event_addAlertSingle(ruslan, firstEvent, alert_master);
	event_addAlertSingle(ruslan, secondEvent, alert_master);
	// subscribing other users including ruslan (for the third event) with alert_common callback function
	event_addAlertSeveral(userArr, userArrSize, thirdEvent, alert_common);
	// main cycle of the program. To break it, press ANY KEY
	int check;
	while (!kbhit()) {
		// creating new measurement
		puts("********************THE NEW MEASUREMENT HAS BEEN TAKEN********************\n");
		Sleep(1000);
		queue_enqueueRand(msrmQueue);

		// checking condition of first event
		check = queue_firstEvent(msrmQueue);
		puts("==========FIRST EVENT==========\n");
		if (check == DATA) {
			puts("Not enough data for the event yet...\n");
		}
		else if (check == YES) {
			// if the condition is fulfilled - the event is triggered for the subscriber (ruslan)
			event_trigger(firstEvent);
		}
		else {
			puts("Nothing special happened...\n");
		}
		puts("===============================\n");
		Sleep(1000);

		// checking condition of second event
		check = queue_secondEvent(msrmQueue);
		puts("==========SECOND EVENT==========\n");
		if (check == DATA) {
			puts("Not enough data for the event yet...\n");
		}
		else if (check == YES) {
			// if the condition is fulfilled - the event is triggered for the subscriber (ruslan)
			event_trigger(secondEvent);
		}
		else {
			puts("Nothing special happened...\n");
		}
		puts("================================\n");
		Sleep(1000);

		// checking condition of third event
		check = queue_thirdEvent(msrmQueue);
		puts("==========THIRD EVENT==========\n");
		if (check == DATA) {
			puts("Not enough data for the event yet...\n");
		}
		else if (check == YES) {
			// if the condition is fulfilled - the event is triggered for the subscribers (all users including ruslan)
			event_trigger(thirdEvent);
		}
		else {
			puts("Nothing special happened...\n");
		}
		puts("================================\n");
		Sleep(1000);
	}

	// freeing events (and alerts)
	event_free(firstEvent);
	event_free(secondEvent);
	event_free(thirdEvent);
	// freeing users
	for (int i = 0; i < userArrSize; i++) {
		user_free(userArr[i]);
	}
	// freeing main queue with measurements
	queue_free(msrmQueue);


	getch(); //neutralize the _kbhit() from main cycle
	puts("Press ANY KEY to exit the program...");
	getch();
	return 0;
}

// first variation of the callback function for ruslan user as the master user
void alert_master(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("\nI'm mr. %s. I'm a chief, and I know about this event:\n", name);
	printf("It's description:\n%s\n\n", desc);

	free(name);
	free(desc);
}

// second variation of the callback function for all the users including ruslan
void alert_common(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("I'm user %s.\n", name);
	printf("I was notified about the fact that some event occured. Description is next:\n%s\n\n", desc);

	free(name);
	free(desc);
}