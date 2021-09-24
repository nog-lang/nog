#ifndef CORE_MEMORY_HPP
#define CORE_MEMORY_HPP

#include <core/types.hpp>

// Just some macros to calculate bytes.
#define KB(x) (x * 1024)
#define MB(x) (x * KB(1) * 1024)
#define GB(x) (x * MB(1) * 1024)

// Reserve virtual memory
extern void *memory_reserve(unsigned long long size);

template <typename T> static T *memory_reserve(unsigned long long size)
{
    return reinterpret_cast<T *>(memory_reserve(size * sizeof(T)));
}

// Commit virtual memory
extern void memory_commit(void *memory, unsigned long long size);

template <typename T> static void memory_commit(void *memory, unsigned long long size)
{
    memory_commit(memory, size * sizeof(T));
}

// Reserve and commit virtual memory
extern void *memory_init(unsigned long long size);

template <typename T> static T *memory_init(unsigned long long size)
{
    return reinterpret_cast<T *>(memory_init(size * sizeof(T)));
}

// Release virtual memory
extern void memory_release(void *memory, unsigned long long size);

template <typename T> static void memory_release(void *memory, unsigned long long size)
{
    memory_release(memory, size * sizeof(T));
}

#endif