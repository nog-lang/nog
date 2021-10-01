#ifndef COMPILER_COMPILER_HPP
#define COMPILER_COMPILER_HPP

#include <compiler/parser.hpp>
#include <compiler/ssa.hpp>
#include <compiler/x64.hpp>

#include <core/list.hpp>

struct Compiler
{
    Parser parser;

    List<SSA>        ir;
    List<BasicBlock> blocks;
    
    uint32 node_id;

    x64Assembler x64;
    
    // Initialize the compiler
    void init(void);

    // Compile
    bool compile(void);

    // Make SSA
    SSA *make_ssa(unsigned int type);

    // Compile the AST to SSA IR
    void compile_to_ir(void);

    // Compile to C backend
    void compile_to_c(void);

    // Compile to JavaScript backend
    void compile_to_js(void);

    // Compile to x64 backend
    void compile_to_x64(void);
};

#endif