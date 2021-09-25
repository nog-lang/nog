#include <core/system.hpp>
#include <core/console.hpp>
#include <compiler/assembler.hpp>

// The default entry point function
int init(int argument_count, char **arguments)
{
    x64Assembler ass;
    ass.init();

    ass.mov_reg_imm32(ass.eax, 13);
    ass.mov_reg_imm32(ass.rax, 97);
    ass.ret();

    console_write(ass.text.data);
    return exit_success;   
}