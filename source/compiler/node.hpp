#ifndef COMPILER_NODE_HPP
#define COMPILER_NODE_HPP

#include <core/types.hpp>
#include <compiler/token.hpp>

enum
{
    node_none,

    node_primitive_type,
    
    node_function,
    node_block,
    node_return,

    node_expression,
};

enum
{
    expression_primary,
    expression_binary,
    expression_unary,
};

enum
{
    primary_number,
};

using NodePointer       = struct Node       *;
using ExpressionPointer = struct Expression *;

struct ExpressionPrimary
{
    union
    {
        float64 as_number;
    };
    
    uint32 type;
};

struct ExpressionBinary
{
    ExpressionPointer left;
    ExpressionPointer right;
    
    uint32 op;
};

struct ExpressionUnary
{
    ExpressionPointer operand;

    uint32 op;
};

struct Expression
{
    union
    {
        ExpressionPrimary as_primary;
        ExpressionBinary  as_binary;
        ExpressionUnary   as_unary;
    };

    uint32 type;
};

struct NodePrimitiveType
{
    bool  is_const;
    Token token;
};

struct NodeFunction
{
    Token       name;
    Token       property;
    NodePointer type;
    NodePointer block;
};

struct NodeBlock
{
    uint32 last_id;
};

struct NodeReturn
{
    NodePointer expression;
};

struct Node
{
    union
    {
        NodePrimitiveType as_primitive_type;
        NodeFunction      as_function;
        NodeBlock         as_block;
        NodeReturn        as_return;

        Expression as_expression;
    };

    uint32 type;

    // Default Constructor
    Node(void)
    {

    }
};

#endif