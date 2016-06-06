#ifndef EXEC_H_INCLUDED
#define EXEC_H_INCLUDED

// Callback function typedef
typedef void(*log_cb_ptr)(std::ostringstream * log_message);

void exec(log_cb_ptr log_cb_func);

#endif // EXEC_H_INCLUDED