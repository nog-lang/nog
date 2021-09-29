#ifndef COMPILER_PARSER_HPP
#define COMPILER_PARSER_HPP

#include <compiler/scanner.hpp>
#include <compiler/node.hpp>
#include <core/list.hpp>
#include <core/dictionary.hpp>

struct Symbol
{
    uint32 flags;
};

struct Type
{
    bool is_user_type;
};

struct Parser
{
    Scanner scanner;
    bool    had_error;

    List<Node>   ast;
    List<uint32> ids;

    Dictionary<StringView, Symbol> symbol_table;
    Dictionary<StringView, Type>   types;

    // Initialize the parser
    void init(void);

    // Show an error with message
    void error(const char *message);

    // Show an error at token with message
    void error(Token token, const char *message);

    // Advance the token
    void advance(void);

    // Match current type?
    bool match(unsigned int type);

    // Consume token with type
    void consume(unsigned int type, const char *message);

    // Make AST node
    Node *make_node(unsigned int type);

    // Learn source globals
    void learn(const char *source);

    // Parse block of statements
    Node *block(void);

    // Parse expression
    Node *expression(void);

    // Parse return statement
    void return_statement(void);

    // Parse statement
    void statement(void);

    // Parse type
    void type(bool is_const);

    // Parse function declaration
    void function_declaration(Node *type, const Token &name);

    // Parse declaration
    void declaration(void);

    // Parse pass
    bool parse(void);
};

#endif