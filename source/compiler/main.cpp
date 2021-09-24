#include <core/system.hpp>
#include <core/console.hpp>
#include <core/file.hpp>

// The default entry point function
int init(int argument_count, char **arguments)
{
    File f;
    file_read(f, ".gitignore");
    console_writeln(f.content);
    return exit_success;   
}