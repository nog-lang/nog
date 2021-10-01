#include <compiler/scanner.hpp>
#include <core/dictionary.hpp>

static Dictionary<StringView, unsigned int> keywords;
static bool                                 allocated = false;

// Is character an identifier?
static bool is_identifier(char character)
{
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character == '_');
}

// Is character a number?
static bool is_number(char character)
{
    return (character >= '0' && character <= '9');
}

// Initialize the scanner
void Scanner::init(const char *_source)
{
    source  = _source;
    start   = source;
    current = source;
    line    = 1;
    column  = 1;

    // Initialize the keywords
    if (!allocated)
    {
        keywords.init();

        keywords.set("const",  token_const);
        keywords.set("void",   token_void);
        keywords.set("bool",   token_bool);
        keywords.set("ubyte",  token_ubyte);
        keywords.set("byte",   token_byte);
        keywords.set("ushort", token_ushort);
        keywords.set("short",  token_short);
        keywords.set("uint",   token_uint);
        keywords.set("int",    token_int);
        keywords.set("ulong",  token_ulong);
        keywords.set("long",   token_long);
        keywords.set("single", token_single);
        keywords.set("double", token_double);
        keywords.set("string", token_string_type);

        keywords.set("null",  token_null);
        keywords.set("true",  token_true);
        keywords.set("false", token_false);

        keywords.set("sizeof", token_sizeof);
        keywords.set("cast",   token_cast);

        keywords.set("struct", token_struct);
        keywords.set("enum",   token_enum);
        
        keywords.set("private", token_private);
        keywords.set("extern",  token_extern);

        keywords.set("if",       token_if);
        keywords.set("else",     token_else);
        keywords.set("while",    token_while);
        keywords.set("for",      token_for);
        keywords.set("break",    token_break);
        keywords.set("continue", token_continue);
        keywords.set("return",   token_return);
        keywords.set("do",       token_do);

        keywords.set("version",   token_version);
        keywords.set("using",     token_using);
        keywords.set("namespace", token_namespace);

        allocated = true;
    }
}

// Advance and get the previous character
char Scanner::advance(void)
{
    ++column;
    ++current;

    return current[-1];
}

// Match current character?
bool Scanner::match(char expected)
{
    if (*current == expected)
    {
        advance();
        return true;
    }

    return false;
}

// Skip whitespace
unsigned int Scanner::skip_whitespace(void)
{
    for (;;)
    {
        switch (*current)
        {
            // Line
            case '\n':
            {
                ++line;
            }

            // Spacing
            case ' ':
            case '\t':
            case '\r':
            {
                advance();
                break;
            }

            // Comment
            case '/':
            {
                // Single line
                if (current[1] == '/')
                {
                    current += 2;

                    while (!match('\n') && *current != '\0')
                        advance();
                }

                // Multiple lines
                else if (current[1] == '*')
                {
                    int pnesting = 1;
                    int nesting  = 1;

                    current += 2;

                    while (nesting > 0)
                    {
                        if (*current == '\0')
                            return make_token("Unterminated block comment.");
                        
                        if (*current == '/' && current[1] == '*')
                        {
                            current += 2;
                            nesting += 1;

                            continue;
                        }

                        if (*current == '*' && current[1] == '/')
                        {
                            current += 2;
                            nesting -= 1;

                            continue;
                        }

                        if (*current == '\n' && (nesting != pnesting))
                        {
                            ++line;
                            pnesting = nesting;
                        }

                        advance();
                    }
                }
                else
                    return token_none;

                break;
            }

            // Not a whitespace
            default:
                return token_none;
        }
    }
}

// Make token
unsigned int Scanner::make_token(unsigned int type)
{
    current_token.type            = type;
    current_token.content.string  = start;
    current_token.content.length  = static_cast<int>(current - start);
    current_token.line            = line;
    current_token.column          = column;

    return type;
}

// Make error token
unsigned int Scanner::make_token(const char *message)
{
    current_token.type            = token_error;
    current_token.content.string  = message;
    current_token.content.length  = string_length(message);
    current_token.line            = line;
    current_token.column          = column;

    return token_error;
}

// Make string token
unsigned int Scanner::make_string_token(void)
{
    while (*current != '"' && *current != '\0')
        advance();

    // Unterminated string?
    if (*current == '\0')
        return make_token("Unterminated string.");

    advance();
    return make_token(token_string);
}

// Make number token
unsigned int Scanner::make_number_token(void)
{
    while (is_number(*current))
        advance();

    if (match('.'))
    {
        while (is_number(*current))
            advance();
    }

    return make_token(token_number);
}

// Make identifier token
unsigned int Scanner::make_identifier_token(void)
{
    while (is_identifier(*current) || is_number(*current))
        advance();

    StringView identifier { start, static_cast<unsigned int>(current - start) };

    if (keywords.exists(identifier))
        return make_token(keywords.get(identifier));

    return make_token(token_identifier);
}

// Make character token
unsigned int Scanner::make_character_token(void)
{
    while (*current != '\'' && *current != '\0')
        advance();

    // Unterminated character?
    if (*current == '\0')
        return make_token("Unterminated character.");

    advance();
    return make_token(token_character);
}

// Get next token
unsigned int Scanner::next_token(void)
{
    char character;

    if (skip_whitespace() == token_error)
        return token_error;

    start          = current;
    previous_token = current_token;

    if (*current == '\0')
        return make_token(token_end);

    character = advance();

    if (is_number(character) || (character == '-' && is_number(*current)))
        return make_number_token();

    if (is_identifier(character))
        return make_identifier_token();

    switch (character)
    {
        case '(':
            return make_token(token_lparen);

        case ')':
            return make_token(token_rparen);
            
        case '{':
            return make_token(token_lbrace);
            
        case '}':
            return make_token(token_rbrace);
            
        case '+':
            return make_token(token_plus);
        
        case '-':
            return make_token(token_minus);
            
        case '*':
            return make_token(token_multiply);
            
        case '/':
            return make_token(token_divide);
            
        case '=':
            return make_token(token_equal);
            
        case ';':
            return make_token(token_semicolon);
            
        case ':':
            return make_token(token_colon);
            
        case ',':
            return make_token(token_comma);
            
        case '.':
            return make_token(token_dot);

        case '"':
            return make_string_token();

        case '\'':
            return make_character_token();
    }

    // Unexpected character
    return make_token("Unexpected character.");
}