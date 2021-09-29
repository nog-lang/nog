#ifndef COMPILER_SCANNER_HPP
#define COMPILER_SCANNER_HPP

#include <compiler/token.hpp>

struct Scanner
{
    Token previous_token;
    Token current_token;

    const char *source;
    const char *start;
    const char *current;

    uint32 line;
    uint32 column;

    // Initialize the scanner
    void init(const char *source);

    // Advance and get the previous character
    char advance(void);

    // Match current character?
    bool match(char expected);

    // Skip whitespace
    unsigned int skip_whitespace(void);

    // Make token
    unsigned int make_token(unsigned int type);

    // Make error token
    unsigned int make_token(const char *message);

    // Make string token
    unsigned int make_string_token(void);

    // Make number token
    unsigned int make_number_token(void);

    // Make identifier token
    unsigned int make_identifier_token(void);

    // Make character token
    unsigned int make_character_token(void);

    // Get next token
    unsigned int next_token(void);
};

#endif