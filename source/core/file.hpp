#ifndef CORE_FILE_HPP
#define CORE_FILE_HPP

#include <core/string.hpp>

#if defined(version_standard)
#include <stdio.h>
#endif

struct File
{
    const char *path;
    char       *content;
    uint32      size;

#if defined(version_standard)
    FILE *handle;
#endif

    // Open file
    bool open(const char *path);

    // Write any value to file
    void write(const void *value, unsigned int size);

    template <typename T> void write(T value)
    {
        write(&value, sizeof(T));
    }

    template <typename T> void write(T *value)
    {
        write(value, sizeof(T));
    }

    // Write string to file
    void write(const char *string);

    // Read file
    bool read(const char *path);

    // Close file
    void close(void);
};

#endif