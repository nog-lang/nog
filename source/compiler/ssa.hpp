#ifndef COMPILER_SSA_HPP
#define COMPILER_SSA_HPP

#include <core/types.hpp>
#include <core/string.hpp>

enum
{
    ssa_value,
    ssa_ret,
};

enum
{
    ssa_value_bool,
    ssa_value_int,
    ssa_value_float,
    ssa_value_string,
};

using SSAPointer = struct SSA *;

struct BasicBlock
{
    SSAPointer start;
    SSAPointer end;
};

struct SSAValue
{
    union
    {
        bool       as_bool;
        int64      as_int;
        float64    as_float;
        StringView as_string;
    };

    uint32 type;
};

struct SSARet
{
    SSAPointer value;
};

struct SSA
{
    union
    {
        SSAValue as_value;
        SSARet   as_ret;
    };

    uint32 type;

    // Default Constructor
    SSA(void)
    {
        
    }
};

#endif