#ifndef COMPILER_CONFIG_HPP
#define COMPILER_CONFIG_HPP

#include <core/list.hpp>
#include <core/file.hpp>

enum
{
    backend_c,
    backend_js,
    backend_x64,
};

struct InputInformation
{
    File file;
    bool parsed;
};

// All the source files
extern List<InputInformation> g_inputs;

// The input information of the main file
extern InputInformation g_input;

// The path of where the output will go
extern const char *g_output;

// The backend to compile
extern uint32 g_backend;

#endif