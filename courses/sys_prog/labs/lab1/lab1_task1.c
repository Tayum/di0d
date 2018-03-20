#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFF 1024

void uppercase(char * str, int length);

int main(int argc, char * argv[]) {

    ssize_t fd_input;
    ssize_t fd_output;
    int bytes_total = 0;
    ssize_t bytes_input;
    ssize_t bytes_output;
    char buff[BUFF];

    if (argc < 3) {
      printf("Missing arguments\n");
      return -1;
    }

    // read
    fd_input = open(argv[1], O_RDONLY);
    if (fd_input == -1) {
      printf("Error while opening %s file for READING\n", argv[1]);
      return -1;
    }

    // write
    fd_output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_output == -1){
      printf("Error while opening %s file for WRITING\n", argv[2]);
      return -1;
    }

    // copy
    while ((bytes_input = read(fd_input, &buff, BUFF)) > 0) {
      // uppercase
      uppercase(buff, bytes_input);

      bytes_output = write(fd_output, &buff, bytes_input);
      if (bytes_input != bytes_output) {
          printf("Error while writing to file: (BYTES_INPUT): %d, (BYTES_OUTPUT): %d\n", bytes_input, bytes_output);
          return -1;
      }
      bytes_total = bytes_total + bytes_output;
    }

    close(fd_input);
    close(fd_output);
    printf("%d bytes have been rewritten\n", bytes_total);
    return 0;
}

void uppercase(char * str, int length) {
  int i;
  for (i = 0; i < length; i++) {
    if ((int)str[i] >= 97 && (int)str[i] <= 122) {
      str[i] = (int)str[i] - 32;
    }
  }
}
