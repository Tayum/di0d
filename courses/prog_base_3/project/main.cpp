#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "exec.h"

// Callback function declaration
void log_func(std::ostringstream * log_recvMsg);

int main(void) {
	srand(time(NULL));

	exec(log_func);

	return 0;
}

// Callback function implementation
void log_func(std::ostringstream * log_recvMsg) {
	std::cout << "[LOG CALLBACK]:\n" << log_recvMsg->str();
}