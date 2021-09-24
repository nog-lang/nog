#include <core/memory.hpp>

#include <stdlib.h>

#ifdef __linux__
#include <sys/mman.h>
#else
#error "This platform is not supported yet."
#endif

// Reserve virtual memory
void *memory_reserve(unsigned long long size)
{
#ifdef __linux__
    void *memory = mmap(0, size, 0, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (memory == nullptr)
        exit(1);

    return memory;
#endif
}

// Commit virtual memory
void memory_commit(void *memory, unsigned long long size)
{
#ifdef __linux__
    if (mprotect(memory, size, PROT_READ | PROT_WRITE) == -1)
        exit(1);
#endif
}

// Reserve and commit virtual memory
void *memory_init(unsigned long long size)
{
    void *memory;

    memory = memory_reserve(size);
    memory_commit(memory, size);

    return memory;
}

// Release virtual memory
void memory_release(void *memory, unsigned long long size)
{
#ifdef __linux__
    if (munmap(memory, size) == -1)
        exit(1);
#endif
}