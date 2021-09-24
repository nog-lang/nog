#ifndef CORE_CONSOLE_HPP
#define CORE_CONSOLE_HPP

#include <core/string.hpp>

#include <initializer_list>

enum
{
    stream_input,
    stream_output,
    stream_error,
};

enum 
{
    console_value_null,
    console_value_string_view,
    console_value_string,
    console_value_char,
    console_value_uint,
    console_value_int,
    console_value_float,
    console_value_bool,
};

struct ConsoleValue
{
    union
    {
        const char *as_string;
        StringView  as_string_view;
        int8        as_char;
        uint64      as_uint;
        int64       as_int;
        float64     as_float;
        bool        as_bool;
    };

    uint32 type;

    // Default constructor
    ConsoleValue(void)
    {
        type = console_value_null;
    }

    // Initialize as null
    ConsoleValue(null_t)
    {
        type = console_value_null;
    }

    // Initialize as string
    ConsoleValue(const char *value)
    {
        as_string = value;
        type      = console_value_string;
    }

    // Initialize as string view
    ConsoleValue(const StringView &value)
    {
        as_string_view = value;
    }

    // Initialize as char
    ConsoleValue(char value)
    {
        as_char = value;
        type    = console_value_char;
    }

    // Initialize as uint
    ConsoleValue(unsigned long long value)
    {
        as_uint = value;
        type   = console_value_uint;
    }

    // Initialize as int
    ConsoleValue(long long value)
    {
        as_int = value;
        type   = console_value_int;
    }

    // Initialize as float
    ConsoleValue(double value)
    {
        as_float = value;
        type     = console_value_float;
    }

    // Initialize as bool
    ConsoleValue(bool value)
    {
        as_bool = value;
        type     = console_value_bool;
    }
};

// Write message to console
extern void console_write(const ConsoleValue &message);

// Write message with line to console
extern void console_writeln(const ConsoleValue &message);

// Write formatted message to console
extern void console_writef(unsigned int stream, const char *format, const std::initializer_list<ConsoleValue> &values);

template <typename... Ts> void console_writef(unsigned int stream, const char *format, Ts... values)
{
    console_writef(stream, format, { values... });
}

#endif