#include <core/string.hpp>
#include <core/console.hpp>
#include <core/memory.hpp>

// Initialize the string builder
void StringBuilder::init(void)
{
    length   = 0;
    capacity = 1024;
    data     = memory_reserve<char>(GB(1));

    // Commit the bytes we're going to use
    memory_commit<char>(data, capacity);

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $yvoid StringBuilder::init(void)$w: Reserving $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
    console_writef(stream_output, "--> $yvoid StringBuilder::init(void)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(capacity));
#endif
}

// Add character to string builder
void StringBuilder::add(char character)
{
    // Check for room
    if (length >= capacity)
    {
        capacity *= 2;
        memory_commit<char>(data, capacity);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid StringBuilder::add(char character)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(capacity));
#endif
    }

    data[length++] = character;
}

// Add string to string builder
void StringBuilder::add(const char *string)
{
    unsigned int _length = string_length(string);

    // Check for room
    if ((length + _length) >= capacity)
    {
        capacity *= 2;
        memory_commit<char>(data, capacity);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid StringBuilder::add(const char *string)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(capacity));
#endif
    }

    for (unsigned int i = 0; i < _length; ++i)
        data[length++] = string[i];
}

// Add string view to string builder
void StringBuilder::add(const StringView &view)
{
    // Check for room
    if ((length + view.length) >= capacity)
    {
        capacity *= 2;
        memory_commit<char>(data, capacity);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid StringBuilder::add(const StringView &view)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(capacity));
#endif
    }

    for (unsigned int i = 0; i < view.length; ++i)
        data[length++] = view.string[i];
}

// Add integer to string builder
void StringBuilder::add(long long value)
{
    char buffer[64];
    to_string(buffer, value);

    add(buffer);
}

// Add float to string builder
void StringBuilder::add(double value)
{
    char buffer[64];
    to_string(buffer, value, 6);

    add(buffer);
}

// Release the string builder memory
void StringBuilder::free(void)
{
    // Release the 1 GB we've reserved
    memory_release<char>(data, GB(1));

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $yvoid StringBuilder::free(void)$w: Releasing $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
#endif
}