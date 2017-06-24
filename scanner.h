#ifndef scanner_h
#define scanner_h

#include <stdbool.h>


typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_EOF,
    TOKEN_ERROR,
} TokenType;

typedef struct {
    TokenType   type;
    const char* start;
    int         length;
    int         line;
} Token;

// A token and it's string representation. Since we can't print
// enums to inspect the TokenTypes in the ouput of the scanner
// we need to store the string representation of each TokenType
// we would like to print.
typedef struct {
    TokenType   type;
    const char* string;
} TokenToString;

const char* ttos(TokenType);
static bool end();
static void skipWhitespace();
static char peekNext();
static Token number();
static bool isAtEnd();
static char peek();
static bool isDigit(char c);
static char advance();
static Token makeToken(TokenType);
void initScanner(const char* source);
Token scanToken();

#endif
