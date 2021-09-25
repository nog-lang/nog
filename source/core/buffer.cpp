#include <core/buffer.hpp>

// Initialize the buffer
void Buffer::init(void)
{
    size = 0;
    room = 1024;
    data = memory_reserve<unsigned char>(GB(1));

    // Commit the bytes we're going to use
    memory_commit<unsigned char>(data, room);

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $yvoid Buffer::init(void)$w: Reserving $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
    console_writef(stream_output, "--> $yvoid Buffer::init(void)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room));
#endif
}

// Release the buffer memory
void Buffer::free(void)
{
    // Release the 1 GB we've reserved
    memory_release<unsigned char>(data, GB(1));

    // Debugging
#if defined(debug)
    console_writef(stream_output, "--> $yvoid Buffer::free(void)$w: Releasing $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
#endif
}