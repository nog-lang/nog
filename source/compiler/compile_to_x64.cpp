#include <compiler/compiler.hpp>

// Compile ret instruction
static void ret(Compiler *compiler, const SSARet &instruction)
{
    // No return value?
    if (!instruction.value)
    {
        compiler->x64.mov_reg_imm32(compiler->x64.eax, 0); // TODO: change this to xor eax, eax
        compiler->x64.ret();
    }
    else if (instruction.value)
    {
        // Constant?
        if (instruction.value->type == ssa_value)
        {
            SSAValue &value = instruction.value->as_value;

            // TODO: support other types
            compiler->x64.mov_reg_imm32(compiler->x64.eax, value.as_float);
            compiler->x64.ret();
        }
    }
}

// Compile to x64 backend
void Compiler::compile_to_x64(void)
{
    // Initialize the assembler
    x64.init();

    // Traverse the IR and generate x64 machine code
    for (unsigned int i = 0; i < blocks.size; ++i)
    {
        BasicBlock &block = blocks.get(i);

        for (SSA *instruction = block.start; instruction < block.end; ++instruction)
        {
            switch (instruction->type)
            {
                // ret
                case ssa_ret:
                {
                    ret(this, instruction->as_ret);
                    break;
                }
            }
        }
    }

    // Show the assembly
    console_write(x64.text.data);
}