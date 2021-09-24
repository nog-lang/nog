#ifndef CORE_COMPARE_HPP
#define CORE_COMPARE_HPP

#include <core/string.hpp>

// Compare any value
template <typename T> static bool compare(T a, T b)
{
    return (a == b);
}

// Compare strings
static bool compare(const char *a, const char *b)
{
    return ((a == b) || string_equals(a, b));
}

// Compare string views
static bool compare(StringView a, StringView b)
{
    return ((a.length == b.length) && string_equals(a.string, b.string, a.length));
}

#endif