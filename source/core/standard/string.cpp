#include <core/string.hpp>

#include <string.h>

// Get string length
unsigned int string_length(const char *string)
{
    return static_cast<unsigned int>(strlen(string));
}

// Are both strings equal?
bool string_equals(const char *a, const char *b, unsigned int length)
{
    if (length == 0)
        return (strcmp(a, b) == 0);
    
    return (strncmp(a, b, length) == 0);
}