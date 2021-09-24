#include <core/file.hpp>
#include <core/memory.hpp>
#include <core/console.hpp>

#include <stdio.h>
#include <stdlib.h>

// Open file
bool file_open(File &file, const char *path)
{
    file.path   = path;
    file.handle = fopen(path, "wb");
    file.size   = 0;

    return (file.handle != nullptr);
}

// Write any value to file
void file_write(File &file, const void *value, unsigned int size)
{
    file.size += size;
    fwrite(value, size, 1, file.handle);
}

// Write string to file
void file_write(File &file, const char *string)
{
    file.size += string_length(string);
    fwrite(string, string_length(string), 1, file.handle);
}

// Read file
bool file_read(File &file, const char *path)
{
    // Open file
    file.path   = path;
    file.handle = fopen(path, "rb");

    if (file.handle == nullptr)
        return false;

    // Get file size
    fseek(file.handle, 0, SEEK_END);
    file.size = ftell(file.handle);
    fseek(file.handle, 0, SEEK_SET);

    // Allocate file content
    file.content = memory_init<char>(file.size + 1);

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $ybool file_read(File &file, const char *path)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(file.size + 1));
#endif

    // Read file
    fread(file.content, file.size, 1, file.handle);
    file.content[file.size] = '\0';

    return true;
}

// Close file
void file_close(File &file)
{
    fclose(file.handle);
}