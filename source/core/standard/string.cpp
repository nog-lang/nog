#include <core/string.hpp>

#include <string.h>

// Get string length
unsigned int string_length(const char *string)
{
    return static_cast<unsigned int>(strlen(string));
}