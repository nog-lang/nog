#include <core/string.hpp>

#include <string.h>
#include <stdio.h>

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

// Convert integer to string
void to_string(char *buffer, long long value)
{
    snprintf(buffer, 64, "%lld", value);
}

// Convert float to string
void to_string(char *buffer, double value, unsigned int precision)
{
    snprintf(buffer, 64, "%.*f", precision, value);
}

// Convert string to integer
long long string_to_integer(const char *string)
{
    long long result;

    sscanf(string, "%lld", &result);
    return result;
}

// Convert string to float
double string_to_float(const char *string)
{
    double result;

    sscanf(string, "%lf", &result);
    return result;
}