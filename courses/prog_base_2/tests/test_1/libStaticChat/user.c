#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chat.h"

struct user_s {
	char name[25];
	int isSubscribed;
	list_t * userMessages;
};

user_t * user_new(char * name) {
	user_t * userSmp = malloc(sizeof(struct user_s));
	strcpy(userSmp->name, name);
	userSmp->isSubscribed = NO;
	return userSmp;
}

// list of messages will be free()'d in chat
void user_free(user_t * self) {
	free(self);
}

char * user_getName(const user_t * self) {
	char * name = malloc((strlen(self->name) + 1) * sizeof(char));
	strcpy(name, self->name);
	return name;
}

void user_subscribe(user_t * user) {
	if (user->isSubscribed == NO) {
		user->isSubscribed = YES;
	}
}

int user_isSubscribed(const user_t * user) {
	if (user->isSubscribed == YES) {
		return YES;
	}
	else {
		return NO;
	}
}

void user_addMsg(user_t * self, message_t * msg) {
	list_push_back(self->userMessages, msg);
}

// free a list with list_free() after usage!
list_t * user_getMessages(const user_t * self) {
	list_t * userMsgList = list_new_copy(self->userMessages);
	return userMsgList;
}



