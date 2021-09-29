#include <compiler/parser.hpp>
#include <compiler/config.hpp>

// Initialize the parser
void Parser::init(void)
{
    had_error = false;

    ast.init();
    ids.init();

    symbol_table.init();
    types.init();

    // Initialize the types
    types.set("void",   { false });
    types.set("bool",   { false });
    types.set("ubyte",  { false });
    types.set("ushort", { false });
    types.set("uint",   { false });
    types.set("ulong",  { false });
    types.set("byte",   { false });
    types.set("short",  { false });
    types.set("int",    { false });
    types.set("long",   { false });
    types.set("single", { false });
    types.set("double", { false });
    types.set("string", { false });
}

// Show an error with message
void Parser::error(const char *message)
{
    had_error = true;
    console_writef(stream_error, "$rError:$* %\n", message);
}

// Show an error at token with message
void Parser::error(Token token, const char *message)
{
    had_error = true;
    console_writef(stream_error, "[line %:%] $rError", token.line, token.column);

    if (token.type == token_end)
        console_writef(stream_error, " at end:$* $w");
    else if (token.type == token_error)
        console_writef(stream_error, ":$* $w");
    else
        console_writef(stream_error, " at $w%$r:$* $w", token.content);

    console_writef(stream_error, message);
    console_writef(stream_error, "\n");
}

// Advance the token
void Parser::advance(void)
{
    for (;;)
    {
        if (scanner.next_token() != token_error)
            break;

        error(scanner.current_token, scanner.current_token.content.string);
    }
}

// Match current type?
bool Parser::match(unsigned int type)
{
    if (scanner.current_token.type == type)
    {
        advance();
        return true;
    }

    return false;
}

// Consume token with type
void Parser::consume(unsigned int type, const char *message)
{
    if (match(type))
        return;

    error(scanner.current_token, message);
}

Node *Parser::make_node(unsigned int type)
{
    Node node;
    node.type = type;

    return &ast.get(ast.add(node));
}

// Learn source globals
void Parser::learn(const char *source)
{
    scanner.init(source);
    scanner.next_token();

    while (!match(token_end))
    {
        scanner.next_token();

        switch (scanner.previous_token.type)
        {
            // Import statement
            // case token_import:
            // {
            //     consume(token_identifier, "Expect module name after 'import'.");

            //     // Save current scanner
            //     Scanner current_scanner = scanner;

            //     // Learn this module globals
            //     learn(g_inputs.get(0).file.content);

            //     // Set scanner back
            //     scanner = current_scanner;
            //     break;
            // }

            // testing
            case token_version:
            {
                console_writeln("VERSION!");

                break;
            }
        }
    }
}

// Parse block of statements
Node *Parser::block(void)
{
    Node      *node       = make_node(node_block);
    NodeBlock &block_node = node->as_block;
    
    while (!match(token_rbrace) && !match(token_end))
        statement();

    // if (scanner.previous_token.type == token_end)
    //     error(scanner.previous_token, "Expected '}' after function statement(s).");

    block_node.last_id = ast.size;
    return node;
}

// Parse expression
Node *Parser::expression(void)
{
    Node *node;

    // Make number node
    if (match(token_number))
    {
        node = make_node(node_expression);

        Expression &expr = node->as_expression;
        expr.type        = expression_primary;

        ExpressionPrimary &primary = expr.as_primary;
        primary.type               = primary_number;
        primary.as_number          = static_cast<float64>(string_to_integer(scanner.previous_token.content.string));
    }

    return node;
}

// Parse return statement
void Parser::return_statement(void)
{
    // Make return node
    NodeReturn &return_node = make_node(node_return)->as_return;

    // No return value?
    if (match(token_semicolon))
        return_node.expression = nullptr;
    else
        return_node.expression = expression();
}

// Parse statement
void Parser::statement(void)
{
    scanner.next_token();

    switch (scanner.previous_token.type)
    {
        // Return statement
        case token_return:
        {
            return_statement();
            break;
        }
    }
}

// Parse type
void Parser::type(bool is_const)
{
    Node  *node;
    Token  name;

    // Make type node
    Type &ty = types.get(scanner.previous_token.content);

    if (ty.is_user_type)
    {
        console_writeln("Handle user type.");
    }
    else
    {
        node = make_node(node_primitive_type);

        NodePrimitiveType &primitive_type_node = node->as_primitive_type;
        primitive_type_node.is_const           = is_const;
        primitive_type_node.token_type         = scanner.previous_token.type;
    }

    consume(token_identifier, "Expected identifier after type.");
    name = scanner.previous_token;

    // Is a function declaration?
    if (match(token_lparen))
        function_declaration(node, name);
}

// Parse function declaration
void Parser::function_declaration(Node *type, const Token &name)
{
    // Make function node
    NodeFunction &function_node = make_node(node_function)->as_function;
    function_node.type          = type;
    function_node.name          = name;

    consume(token_rparen, "Expected ')' after function parameters.");

    // Make block node
    consume(token_lbrace, "Expected '{'.");
    function_node.block = block();
}

// Parse declaration
void Parser::declaration(void)
{
    scanner.next_token();

    // A function or variable declaration?
    if (types.exists(scanner.previous_token.content))
    {
        type(false);
        return;
    }

    switch (scanner.previous_token.type)
    {
        // Constant type
        case token_const:
        {
            scanner.next_token();
            type(true);

            break;
        }
    }
}

// Parse pass
bool Parser::parse(void)
{
    // Learn every global first
    // learn(g_input.file.content);

    // Parse every declaration
    scanner.init(g_input.file.content);
    scanner.next_token();

    while (!match(token_end))
        declaration();

    return !had_error;
}