#ifndef COMPILER_x64_HPP
#define COMPILER_x64_HPP

#include <core/buffer.hpp>
#include <core/string.hpp>

struct x64Assembler
{
    struct x64Register
    {
        uint32      index;
        uint32      size;
        const char *name;
    };

    x64Register eax { 0, 4, "eax" };
    x64Register rax { 0, 8, "rax" };

    Buffer        code;
    StringBuilder text;

    // Initialize the assembler
    void init(void);

    // Release the assembler memory
    void free(void);

    // MOV
    void mov_reg_imm32(const x64Register &reg, int value);

    // RET
    void ret(void);
};

#endif