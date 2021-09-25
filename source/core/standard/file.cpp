#include <core/file.hpp>
#include <core/memory.hpp>
#include <core/console.hpp>

#include <stdio.h>
#include <stdlib.h>

// Open file
bool File::open(const char *path_)
{
    path   = path_;
    handle = fopen(path, "wb");
    size   = 0;

    return (handle != nullptr);
}

// Write any value to file
void File::write(const void *value, unsigned int size)
{
    size += size;
    fwrite(value, size, 1, handle);
}

// Write string to file
void File::write(const char *string)
{
    size += string_length(string);
    fwrite(string, string_length(string), 1, handle);
}

// Read file
bool File::read(const char *_path)
{
    // Open file
    path   = _path;
    handle = fopen(path, "rb");

    if (handle == nullptr)
        return false;

    // Get file size
    fseek(handle, 0, SEEK_END);
    size = ftell(handle);
    fseek(handle, 0, SEEK_SET);

    // Allocate file content
    content = memory_init<char>(size + 1);

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $ybool File::read(const char *path)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(size + 1));
#endif

    // Read file
    fread(content, size, 1, handle);
    content[size] = '\0';

    return true;
}

// Close file
void File::close(void)
{
    fclose(handle);
}