#ifndef CORE_STRING_HPP
#define CORE_STRING_HPP

#include <core/types.hpp>

// Get string length
extern unsigned int string_length(const char *string);

// Are both strings equal?
extern bool string_equals(const char *a, const char *b, unsigned int length = 0);

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

    // Get character from string view
    char operator[](unsigned int index)
    {
        return string[index];
    }
};

struct StringBuilder
{
    uint32  length;
    uint32  capacity;
    char   *data;

    // Initialize the string builder
    void init(void);

    // Add character to string builder
    void add(char character);

    // Add string to string builder
    void add(const char *string);

    // Add string view to string builder
    void add(const StringView &string);

    // Release the string builder memory
    void free(void);

    // Get string builder as string
    operator const char *(void)
    {
        return reinterpret_cast<const char *>(data);
    }

    // Get character from string builder
    char operator[](unsigned int index)
    {
        return data[index];
    }
};

#endif