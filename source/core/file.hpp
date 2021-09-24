#ifndef CORE_FILE_HPP
#define CORE_FILE_HPP

#include <core/string.hpp>

#if defined(version_standard)
#include <stdio.h>
#endif

struct File
{
    const char *path;
    int8       *content;
    uint32      size;

#if defined(version_standard)
    FILE *handle;
#endif
};

// Open file
extern bool file_open(File &file, const char *path);

// Write any value to file
extern void file_write(File &file, const void *value, unsigned int size);

template <typename T> void file_write(File &file, T value)
{
    file_write(file, &value, sizeof(T));
}

template <typename T> void file_write(File &file, T *value)
{
    file_write(file, value, sizeof(T));
}

// Write string to file
extern void file_write(File &file, const char *string);

// Read file
extern bool file_read(File &file, const char *path);

// Close file
extern void file_close(File &file);

#endif