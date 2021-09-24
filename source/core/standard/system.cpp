#include <core/system.hpp>

#include <stdlib.h>

// The default entry point function for C++ standard library
int main(int argc, char *argv[])
{
    return init(argc, argv);
}

// Quit from program
void quit(int code)
{
    exit(code);
}