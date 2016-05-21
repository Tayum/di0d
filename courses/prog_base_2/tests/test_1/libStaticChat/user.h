/* user.h AND user.c DESCRIBES THE USERS THAT ARE SUBSCRIBING FOR NOTIFICATIONS */

#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "chat.h"

typedef struct user_s user_t;

user_t * user_new(char * name);
void user_free(user_t * self);

// free() a line after usage!
char * user_getName(const user_t * self);

void user_subscribe(user_t * user);
int user_isSubscribed(const user_t * user);
void user_addMsg(user_t * self, message_t * msg);

// free a list with list_free() after usage!
list_t * user_getMessages(const user_t * self);

#endif //USER_H_INCLUDED
