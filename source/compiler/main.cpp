#include <core/system.hpp>
#include <core/console.hpp>

#include <compiler/config.hpp>
#include <compiler/compiler.hpp>

// Parse command line arguments
static bool parse_args(unsigned int argument_count, char **arguments)
{
    // Initialize the inputs
    InputInformation input;
    input.parsed = false;

    g_inputs.init();

    bool is_import_path = false;

    // Parse every argument
    for (int i = 1; i < argument_count; ++i)
    {
        const char *argument = arguments[i];
        
        // Output path?
        if (string_equals(argument, "--output", 9))
            g_output = arguments[++i];

        // Import path?
        else if (string_equals(argument, "-I", 2))
            is_import_path = true;

        else
        {
            const char *position = string_find(argument, '.');

            if (is_import_path)
            {
                // Make sure it's a nog file
                if (position != nullptr && string_equals(position, ".nog", 3))
                {
                    // Read file
                    if (!input.file.read(argument))
                    {
                        console_writef(stream_error, "$rError: $wFailed to read import path file '%'.$*\n", argument);
                        return false;
                    }

                    // Add input
                    g_inputs.add(input);
                }
                else
                {
                    console_writef(stream_error, "$rError: $wFile extension needs to end with '.nog'.$*\n");
                    return false;
                }
            }
            else
            {
                g_input.parsed = true;

                // Make sure it's a nog file
                if (position != nullptr && string_equals(position, ".nog", 3))
                {
                    // Read file
                    if (!g_input.file.read(argument))
                    {
                        console_writef(stream_error, "$rError: $wFailed to read input file '%'.$*\n", argument);
                        return false;
                    }
                }
                else
                {
                    console_writef(stream_error, "$rError: $wFile extension needs to end with '.nog'.$*\n");
                    return false;
                }
            }
        }
    }

    // No input file?
    if (g_inputs.size == 0 && g_input.file.path == nullptr)
    {
        console_writef(stream_error, "$rError: $wNo input files.$*\n");
        return false;
    }

    return true;
}

// The default entry point function
int init(int argument_count, char **arguments)
{
    // Parse command line arguments
    if (!parse_args(argument_count, arguments))
        return exit_failure;

    Compiler compiler;

    compiler.init();
    compiler.compile();

    return exit_success;   
}