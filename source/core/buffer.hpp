#ifndef CORE_BUFFER_HPP
#define CORE_BUFFER_HPP

#include <core/list.hpp>
#include <core/console.hpp>

struct Buffer
{
    uint32  size;
    uint32  room;
    uint8  *data;

    // Initialize the buffer
    void init(void);

    // Release the buffer memory
    void free(void);

    // Write bytes to buffer
    template <typename T> void write(T value)
    {
        // Check for room
        if ((size + sizeof(T)) >= room)
        {
            room *= 2;
            memory_commit<unsigned char>(data, room);

            // Debugging
#if defined(debug)
            console_writef(stream_output, "--> $yvoid Buffer::write(T value)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room));
#endif
        }

        *reinterpret_cast<T *>(data + size)  = value;
        size                                += sizeof(T);
    }

    // Get byte from buffer
    unsigned char operator[](unsigned int index)
    {
        return data[index];
    }
};

#endif