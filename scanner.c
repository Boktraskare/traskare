#include <stdio.h>
#include "scanner.h"
#include <string.h>

/* ----------------------------------------------------------

   SCANNER

   This file will be used by the parser.c file. The parser can 
   then initialize the scanner with the source code and call
   scanToken() whenever it's ready to advance to the next token.

   This means that the lexer analyses the source for tokens "on
   the fly". No list of tokens is ever buffered. This detail is,
   however, completely transparent to the parser. All the parser
   needs is a way to get the next token, and instead of giving
   the parser a list of tokens to walk, it is given a parser
   to call scanToken() on, which has the same effect. this saves
   us from having to buffer a list of tokens between the scanner
   and the parser.

   ---------------------------------------------------------- */

// For debugging
static TokenToString tokenToString[] = {
    {TOKEN_NUMBER, "TOKEN_NUMBER"}, 
    {TOKEN_PLUS,   "TOKEN_PLUS"}, 
    {TOKEN_EOF,    "TOKEN_EOF"}, 
    {TOKEN_ERROR,  "TOKEN_ERROR"}, 
};

const char* ttos(TokenType type) {
    TokenToString* table = tokenToString;
    TokenToString* endOfTable = table + sizeof(tokenToString)/sizeof(tokenToString[0]);

    while (table < endOfTable) {
        if (table->type == type) {
            return table->string;
        }

        table++;
    }

    return "NO_STRING_REPRESENTATION";
}

typedef struct {
    // The complete source file we are walking char by char.
    const char* source;

    // lexemeStart and current is needed when constructing tokens
    // for the parser. When we reach the end of the token we are
    // certain that the current lexeme to make into a token is in
    // the span och lexemeStart and current.
    const char* tokenStart;
    const char* current;

    // The line count needs to be maintained throughout scanning,
    // otherwise we can't tell the user on what line the eventual
    // errors occurs.
    int line;
} Scanner;

// Global scanner object.
Scanner scanner;

void initScanner(const char* source) {
    scanner.source      = source;
    scanner.tokenStart  = source;
    scanner.current     = source;
    scanner.line        = 1;    
}

static void skipWhitespace() {
    while (true) {
        switch(peek()) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;

            case '\n':
                scanner.line++;
                advance();
                break;

            default:
                return;
        }
    }
}

static bool end() {
    return *scanner.current == '\0';
}

// Scan for token and switch into the correct case with the 
// default case being numbers.
Token scanToken() {
    skipWhitespace();
    scanner.tokenStart = scanner.current;

    if (*scanner.current == '\0') {
        return makeToken(TOKEN_EOF);
    }

    char c = advance();

    switch (c) {
        case '+': return makeToken(TOKEN_PLUS); break;

        default:
                  if(isDigit(c)) {
                      return number();
                  }
    }

    return makeToken(TOKEN_ERROR);
}

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.tokenStart;
    token.length = (int) (scanner.current - scanner.tokenStart);
    token.line = scanner.line;

    return token;
}

// Check if it is a number
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Advance the scanner to the next character
static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

// Look at the current character
static char peek() {
    return *scanner.current;
}

// What to do if the character is a number
static Token number() {
    while (isDigit(peek())) advance();
    return makeToken(TOKEN_NUMBER);
}
