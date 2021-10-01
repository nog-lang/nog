#include <compiler/compiler.hpp>
#include <compiler/config.hpp>

// Initialize the compiler
void Compiler::init(void)
{
    parser.init();
}

// Make SSA
SSA *Compiler::make_ssa(unsigned int type)
{
    SSA ssa;
    ssa.type = type;

    return &ir.get(ir.add(ssa));
}

// Compile
bool Compiler::compile(void)
{
    // Parse pass
    if (!parser.parse())
        return false;

    // Check for backend
    switch (g_backend)
    {
        // x64
        case backend_x64:
        {
            compile_to_ir();
            compile_to_x64();
            break;
        }
    }

    return true;
}