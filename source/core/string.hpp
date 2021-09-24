#ifndef CORE_STRING_HPP
#define CORE_STRING_HPP

#include <core/types.hpp>

// Get string length
extern unsigned int string_length(const char *string);

struct StringView
{
    const char *string;
    uint32      length;

    // Initialize without length
    StringView(const char *value)
    {
        string = value;
        length = string_length(value);
    }

    // Initialize with length
    StringView(const char *value, unsigned int _length)
    {
        string = value;
        length = _length;
    }

    // Get string view as string
    operator const char *(void)
    {
        return string;
    }
};

#endif