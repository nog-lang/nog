#include <core/console.hpp>

#include <stdio.h>

// Write console value to console stream
static void console_value_write(unsigned int stream, const ConsoleValue &value)
{
    // Console streams as C++ standard library streams
    FILE *streams[]
    {
        stdin,
        stdout,
        stderr,
    };

    switch (value.type)
    {
        case console_value_null:
        {
            fprintf(streams[stream], "%s", "null");
            break;
        }

        case console_value_string:
        {
            fprintf(streams[stream], "%s", value.as_string);
            break;
        }

        case console_value_string_view:
        {
            fprintf(streams[stream], "%.*s", value.as_string_view.length, value.as_string_view.string);
            break;
        }

        case console_value_char:
        {
            fprintf(streams[stream], "%c", value.as_char);
            break;
        }

        case console_value_uint:
        {
            fprintf(streams[stream], "%llu", value.as_uint);
            break;
        }

        case console_value_int:
        {
            fprintf(streams[stream], "%lld", value.as_int);
            break;
        }

        case console_value_float:
        {
            fprintf(streams[stream], "%lf", value.as_float);
            break;
        }

        case console_value_bool:
        {
            fprintf(streams[stream], "%s", (value.as_bool) ? "true" : "false");
            break;
        }
    }
}

// Write message to console
void console_write(const ConsoleValue &message)
{
    console_value_write(stream_output, message);
}

// Write message with line to console
void console_writeln(const ConsoleValue &message)
{
    console_value_write(stream_output, message);
    puts("");
}

// Write formatted message to console
void console_writef(unsigned int stream, const char *format, const std::initializer_list<ConsoleValue> &values)
{
    // Console streams as C++ standard library streams
    FILE *streams[]
    {
        stdin,
        stdout,
        stderr,
    };

    const ConsoleValue *ptr = values.begin();

    while (*format)
    {
        switch (*format)
        {
            // Value
            case '%':
            {
                console_value_write(stream, *(ptr++));
                break;
            }

            // Color
            case '$':
            {   
                ++format;

                switch (*format)
                {
                    // Normal yellow
                    case 'y':
                    {
                        fprintf(streams[stream], "\033[0;33m");
                        break;
                    }

                    // Bold yellow
                    case 'Y':
                    {
                        fprintf(streams[stream], "\033[1;33m");
                        break;
                    }

                    // Normal red
                    case 'r':
                    {
                        fprintf(streams[stream], "\033[0;31m");
                        break;
                    }

                    // Bold red
                    case 'R':
                    {
                        fprintf(streams[stream], "\033[1;31m");
                        break;
                    }

                    // Normal white
                    case 'w':
                    {
                        fprintf(streams[stream], "\033[0;37m");
                        break;
                    }

                    // Bold white
                    case 'W':
                    {
                        fprintf(streams[stream], "\033[1;37m");
                        break;
                    }

                    // Reset color
                    case '*':
                    {
                        fprintf(streams[stream], "\033[0m");
                        break;
                    }

                    // Not a color
                    default:
                    {
                        fprintf(streams[stream], "%c", '$');
                        fprintf(streams[stream], "%c", *format);
                        break;
                    }
                }
                break;
            }

            // Character
            default:
            {
                fprintf(streams[stream], "%c", *format);
                break;
            }
        }

        ++format;
    }
}
