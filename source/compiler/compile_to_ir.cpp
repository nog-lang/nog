#include <compiler/compiler.hpp>
#include <compiler/ssa.hpp>

// Compile primary expression
static SSA *primary(Compiler *compiler, const ExpressionPrimary &primary)
{
    switch (primary.type)
    {
        // Number
        case primary_number:
        {
            SSA      *ssa   = compiler->make_ssa(ssa_value);
            SSAValue &value = ssa->as_value;
            value.type      = ssa_value_float;
            value.as_float  = primary.as_number;

            return ssa;
        }
    }

    return nullptr;
}

// Compile expression
static SSA *expression(Compiler *compiler, const Expression &expression)
{
    switch (expression.type)
    {
        // Primary expression
        case expression_primary:
            return primary(compiler, expression.as_primary);
    }

    return nullptr;
}

// Compile statement
static void statement(Compiler *compiler)
{
    Node &node = compiler->parser.ast.get(compiler->node_id++);

    switch (node.type)
    {
        // Return statement
        case node_return:
        {
            NodeReturn &return_node = node.as_return;
            SSARet     &ret         = compiler->make_ssa(ssa_ret)->as_ret;

            if (!return_node.expression)
                ret.value = nullptr;
            else
                ret.value = expression(compiler, return_node.expression->as_expression);
            break;
        }
    }
}

// Compile the AST to SSA IR
void Compiler::compile_to_ir(void)
{
    // Initialize everything before compiling
    ir.init();
    blocks.init();

    // Traverse the AST and generate the IR
    for (node_id = 0; node_id < parser.ast.size; ++node_id)
    {
        Node &node = parser.ast.get(node_id);

        switch (node.type)
        {
            // Block of statements
            case node_block:
            {
                NodeBlock &block_node = node.as_block;

                BasicBlock block;
                block.start = (ir.data + ir.size);

                while (node_id < block_node.last_id)
                    statement(this);

                block.end = (ir.data + ir.size);
                blocks.add(block);
                break;
            }
        }
    }
}