#include <compiler/compiler.hpp>

// Initialize the compiler
void Compiler::init(void)
{
    parser.init();
}

// Compile
bool Compiler::compile(void)
{
    // Parse pass
    if (!parser.parse())
        return false;

    // Traverse the AST for testing
    for (int i = 0; i < parser.ast.size; ++i)
    {
        console_writeln(parser.ast.get(i).type);
    }

    return true;
}