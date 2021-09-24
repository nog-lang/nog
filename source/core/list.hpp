#ifndef CORE_LIST_HPP
#define CORE_LIST_HPP

#include <core/memory.hpp>
#include <core/compare.hpp>

template <typename T> struct List
{
    T      *data;
    uint32  size;
    uint32  room;

    // Initialize the list
    void init(void)
    {
        size = 0;
        room = 1;
        data = memory_reserve<T>(GB(1));

        // Commit the bytes we're going to use
        memory_commit<T>(data, room);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid List<K, V>::init(void)$w: Reserving $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
        console_writef(stream_output, "--> $yvoid List<K, V>::init(void)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room * sizeof(T)));
#endif
    }

    // Add value to list
    unsigned int add(const T &value)
    {
        // Check for room
        if (size >= room)
        {
            room *= 2;
            memory_commit<T>(data, room);

            // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yunsigned int List<K, V>::add(const T &value)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room * sizeof(T)));
#endif
        }

        data[size++] = value;
        return (size - 1);
    }

    // Get value from list by index
    T &get(unsigned int index)
    {
        return data[index];
    }

    // Does key exists in list?
    bool exists(const T &key)
    {
        for (int i = 0; i < size; ++i)
        {
            if (compare(key, data[i]))
                return true;
        }

        return false;
    }

    // Release the list memory
    void free(void)
    {
        // Release the 1 GB we've reserved
        memory_release<T>(data, GB(1));

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid List<K, V>::free(void)$w: Releasing $y%$* bytes of memory.\n", static_cast<unsigned long long>(GB(1)));
#endif
    }
};

#endif