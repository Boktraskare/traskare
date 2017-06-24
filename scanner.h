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
