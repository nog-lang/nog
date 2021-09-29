#include <core/memory.hpp>
#include <core/math.hpp>

// Initialize the bump allocator
void BumpAllocator::init(void)
{
    data = memory_reserve<unsigned char>(GB(1));
    size = 0;
    room = 1024;

    memory_commit<unsigned char>(data, room);
}

// Allocate 
void *BumpAllocator::allocate(unsigned long long _size)
{
    void *memory;

    memory  = reinterpret_cast<void *>(data + size);
    size   += _size;

    if (size >= room)
    {
        room = math_max(size * 2, size + _size);
        memory_commit<unsigned char>(data, room);
    }
    
    return memory; 
}