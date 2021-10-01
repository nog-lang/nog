#include <compiler/config.hpp>

// All the source files
List<InputInformation> g_inputs;

// The input information of the main file
InputInformation g_input;

// The path of where the output will go
const char *g_output = "out/";

// The backend to compile
uint32 g_backend = backend_c;