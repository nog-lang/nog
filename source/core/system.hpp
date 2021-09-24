#ifndef CORE_SYSTEM_HPP
#define CORE_SYSTEM_HPP

enum
{
    exit_success,
    exit_failure,
};

// The default entry point function
extern int init(int argument_count, char **arguments);

// Quit from program
extern void quit(int code);

#endif