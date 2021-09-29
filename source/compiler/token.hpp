#ifndef COMPILER_TOKEN_HPP
#define COMPILER_TOKEN_HPP

#include <core/string.hpp>

enum
{
    token_none,
    token_end,
    token_error,

    token_string,
    token_identifier,
    token_number,
    token_character,

    token_lparen,
    token_rparen,
    token_lbrace,
    token_rbrace,
    token_plus,
    token_minus,
    token_multiply,
    token_divide,
    token_equal,
    token_semicolon,
    token_colon,
    token_comma,
    token_dot,

    token_const,
    token_void,
    token_bool,
    token_ubyte,
    token_ushort,
    token_uint,
    token_ulong,
    token_byte,
    token_short,
    token_int,
    token_long,
    token_single,
    token_double,
    token_string_type,

    token_null,
    token_true,
    token_false,

    token_sizeof,
    token_cast,

    token_struct,
    token_enum,

    token_private,
    token_extern,

    token_if,
    token_else,
    token_while,
    token_for,
    token_break,
    token_continue,
    token_return,
    token_do,

    token_version,
    token_using,
    token_namespace,
};

struct Token
{
    uint32 type;
    uint32 line;
    uint32 column;

    StringView content;

    // Default constructor
    Token(void)
    {
        type   = token_end;
        line   = 0;
        column = 0;
    }
};

#endif