#ifndef CORE_MAP_HPP
#define CORE_MAP_HPP

#include <core/memory.hpp>
#include <core/hash.hpp>
#include <core/compare.hpp>

template <typename K, typename V> struct Dictionary
{
    struct Entry
    {
        K    key;
        V    value;
        bool used;
    };

    uint32  room;
    uint32  size;
    Entry  *data;

    // Initialize the dictionary
    void init(void)
    {
        size = 0;
        room = 64;
        data = memory_init<Entry>(room);

        // Clear all the dictionary entries
        for (int i = 0; i < room; ++i)
            data[i].used = false;

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid Dictionary<K, V>::init(void)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room * sizeof(Entry)));
#endif
    }

    // Find entry 
    Entry *find(Entry *where, const K &key)
    {
        Entry *entry;

        // Hash key and get entry key index
        unsigned int index = (hash(key) % room);

        // Find an available entry
        for (;;)
        {
            entry = &where[index];

            // Check if the key is valid
            if (!entry->used)
                return entry;
            else if (compare(entry->key, key))
                return entry;
            
            // We probably collided here, so increase the index.
            index = ((index + 1) % room);
        }
    }

    // Adjust the dictionary data
    void adjust(void)
    {
        Entry        *new_data;
        Entry        *entry;
        Entry        *destination;
        unsigned int  old_room;

        old_room  = room;
        room     *= 2;
        new_data  = memory_init<Entry>(room);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid Dictionary<K, V>::adjust(void)$w: Committing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room * sizeof(Entry)));
#endif

        // Clear all the new entries
        for (int i = 0; i < room; ++i)
            new_data[i].used = false;

        // Relocate old entries
        for (int i = 0; i < room; ++i)
        {
            entry = &data[i];

            // Is entry empty?
            if (!entry->used)
                continue;

            destination        = find(new_data, entry->key);
            destination->key   = entry->key;
            destination->value = entry->value;
            destination->used  = true;
        }

        // Release the old data
        memory_release<Entry>(data, old_room);

        // Replace old data
        data = new_data;
    }

    // Set dictionary key value
    void set(const K &key, const V &value)
    {
        // Check for room
        if (size >= room)
            adjust();

        // Find available entry
        Entry *entry = find(data, key);

        // Is it a new entry?
        if (!entry->used)
            ++size;

        // Set new entry values
        entry->key   = key;
        entry->value = value;
        entry->used  = true;
    }

    // Get dictionary key value
    V &get(const K &key)
    {
        // Find the entry
        Entry *entry = find(data, key);
        return entry->value;
    }

    // Does key exists in dictionary?
    bool exists(const K &key)
    {
        // Make sure the dictionary is not empty
        if (size == 0)
            return false;

        // Find the entry
        Entry *entry = find(data, key);
        return entry->used;
    }

    // Release the dictionary memory
    void free(void)
    {
        // Release the memory we've reserved
        memory_release<Entry>(data, room);

        // Debugging
#if defined(debug)
        console_writef(stream_output, "--> $yvoid Dictionary<K, V>::free(void)$w: Releasing $y%$* bytes of memory.\n", static_cast<unsigned long long>(room * sizeof(Entry)));
#endif
    }
};

#endif