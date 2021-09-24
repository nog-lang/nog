#include <core/system.hpp>
#include <core/console.hpp>
#include <core/dictionary.hpp>

// The default entry point function
int init(int argument_count, char **arguments)
{
    Dictionary<const char *, const char *> d;
    d.init();

    d.set("fuck", "hi");
    d.set("good", "lol");
    d.set("gaood", "loal");

    console_writeln(d.get("fuck"));
    console_writeln(d.get("good"));
    console_writeln(d.get("gaood"));
    return exit_success;   
}