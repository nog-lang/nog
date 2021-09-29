#ifndef COMPILER_COMPILER_HPP
#define COMPILER_COMPILER_HPP

#include <compiler/parser.hpp>

struct Compiler
{
    Parser parser;
    
    // Initialize the compiler
    void init(void);

    // Compile
    bool compile(void);
};

#endif