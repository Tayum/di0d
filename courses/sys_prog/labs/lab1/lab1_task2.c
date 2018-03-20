#include <stdio.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF 1024
#define SEC 5
#define USEC 0

int main(int argc, char * argv[]) {
    char * str_input;
    char buff[BUFF + 1];

    int select_return;

    fd_set rfds;
    struct timeval tv;

    if (argc < 2) {
      printf("Missing arguments\n");
      return -1;
    }

    // input
    str_input = argv[1];

    while(1) {
      // Set TV struct
      tv.tv_sec = SEC;
      tv.tv_usec = USEC;

      // clear list
      FD_ZERO(&rfds);
      // set STDIN byte
      FD_SET(STDIN_FILENO, &rfds);

      select_return = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);

      if (select_return == -1) {
        printf("ERROR while calling select()");
        return -1;
      }
      else if (select_return == 0) {
        printf("ID: %s\nWARN: No data within five seconds; launching select() again...\n", str_input);
        continue;
      }
      else {
        read(STDIN_FILENO, &buff, BUFF);
        buff[BUFF] = '\0';
        printf("ID: %s\nSUCC: Data: \"%s\"\n", str_input, buff);
        break;
      }
    }

    return 0;
}
