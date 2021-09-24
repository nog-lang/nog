#ifndef CORE_HASH_HPP
#define CORE_HASH_HPP

#include <core/string.hpp>

// Hash integer
static unsigned long long hash(long long key)
{
	unsigned long long hash = key;

	hash = (hash + 0x7ed55d16) + (hash << 12);
	hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
	hash = (hash + 0x165667b1) + (hash << 5);
	hash = (hash + 0xd3a2646c) ^ (hash << 9);
	hash = (hash + 0xfd7046c5) + (hash << 3);
	hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);

	return hash;
}

// Hash string
static unsigned long long hash(const char *key)
{
    unsigned long long hash = 5381;
    int                   c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// Hash ByteString
static unsigned long long hash(const StringView &key)
{
    unsigned long long hash = 5381;
    int                   c;

    for (int i = 0; i < key.length; ++i)
        hash = ((hash << 5) + hash) + key.string[i];

    return hash;
}

#endif