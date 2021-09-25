#include <compiler/assembler.hpp>

// Initialize the assembler
void x64Assembler::init(void)
{
    code.init();
    text.init();
}

// Release the assembler memory
void x64Assembler::free(void)
{
    code.free();
    text.free();
}

// MOV
void x64Assembler::mov_reg_imm32(const x64Register &reg, int value)
{
    code.write<unsigned char>(0xB8 + static_cast<unsigned char>(reg.index));
    code.write<int>(value);
    text.add("\tmov ");
    text.add(reg.name);
    text.add(", ");
    text.add(value);
    text.add("\n");
}

// RET
void x64Assembler::ret(void)
{
    code.write<unsigned char>(0xC3);
    text.add("\tret\n");
}