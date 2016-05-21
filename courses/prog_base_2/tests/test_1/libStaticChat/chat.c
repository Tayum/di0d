#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//====================ALERT STRUCTURE====================

struct alert_s {
	user_t * receiver;
	alert func;
};

typedef struct alert_s alert_t;


void alert_free(alert_t * self) {
	free(self);
}

/*
void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert function) {
alert_t * alertSmp = malloc(sizeof(struct alert_s));
alertSmp->receiver = userPtr;
alertSmp->func = function;
alertArr_addLast(evPtr->alert_array, alertSmp);
}*/

//====================CHAT STRUCTURE====================

struct chat_s {
	char chatName[25];
	list_t * userList;
	list_t * messageList;
};


chat_t * chat_new(char * chatName) {
	chat_t * chatSmp = malloc(sizeof(struct chat_s));
	strcpy(chatSmp->chatName, chatName);
	chatSmp->messageList = list_new();

	return chatSmp;
}

void chat_free(chat_t * self) {

	int msgAmount = list_getSize(self->messageList);
	for (int i = 0; i < msgAmount; i++) {
		message_free((message_t *)list_pop_back(self->messageList));
	}
	list_free(self->messageList);

	int userAmount = list_getSize(self->userList);
	for (int i = 0; i < userAmount; i++) {
		message_free((user_t *)list_pop_back(self->userList));
	}
	list_free(self->messageList);

	free(self);
}

// free() a line after usage!
char * chat_getName(const chat_t * self) {
	char * chatName = malloc((strlen(self->chatName) + 1) * sizeof(char));
	strcpy(chatName, self->chatName);
	return chatName;
}

void chat_setName(chat_t * self, const char * newChatName) {
	strcpy(self->chatName, newChatName);
}

// free a list with list_free() after usage!
list_t * chat_getUserList(const chat_t * self) {
	list_t * userList = list_new();
	userList = list_new_copy(self->userList);
	return userList;
}

// free a list with list_free() after usage!
list_t * chat_getLastMessages(const chat_t * self, int amount) {
	if (amount <= 0 || amount > list_getSize(self->messageList)) {
		return NULL;
	}

	list_t * msgList = list_new_copy(self->messageList);

	int msgAmount = list_getSize(msgList);
	for (int i = 0; i < msgAmount; i++) {
		message_free((message_t *)list_remove(msgList, 0));
	}

	return msgList;
}

void chat_addUser(chat_t * self, user_t * user) {
	if (user_isSubscribed(user) == NO) {
		user_subscribe(user);
		list_push_back(self->userList, user);
	}
}

// NOT READY!
void chat_sendMessage(chat_t * self, user_t * userSender, message_t * msg, alert alertFunc) {
	list_push_back(self->messageList, msg);
	// add notification to all users if they are subscribed
}

// add func for notificating only some users
// void chat_sendMessageToSome(chat_t * self, user_t * userSender, message_t * msg, alert_alertFunc)

//====================MESSAGE STRUCTURE====================

struct message_s {
	char message[1000];
	struct tm * currentTime;
};


message_t * message_new(char * msg) {
	message_t * msgSmp = malloc(sizeof(struct message_s));
	strcpy(msgSmp->message, msg);

	time_t curTime;
	time(&curTime);
	msgSmp->currentTime = localtime(&curTime);

	return msgSmp;
}

void message_free(message_t * self) {
	free(self);
}
