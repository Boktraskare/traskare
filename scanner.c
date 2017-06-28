#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"
#include "token.h"

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

   TODO: Implement "-", "*" and "/".

   ---------------------------------------------------------- */

// Function prototypes. These are static which means they won't
// be visible outside this compilation unit, which also means we
// don't declare them in the header. Functions which are supposed
// to be called from elsewhere, such as scanToken(), are declared 
// in a header file to be included by external .c files.
static bool end();
static void skipWhitespace();
static char peekNext();
static Token number();
static bool isAtEnd();
static char peek();
static bool isDigit(char c);
static char advance();
static Token makeToken(TokenType);

typedef struct {
    // The complete source file we are walking char by char.
    const char* source;

    // lexemeStart and current is needed when constructing tokens
    // for the parser. When we reach the end of the token we are
    // certain that the current lexeme to make into a token is in
    // the span och lexemeStart and current.
    const char* lexemeStart;
    const char* current;

    // The line count needs to be maintained throughout scanning,
    // otherwise we can't tell the user on what line the eventual
    // errors occurs.
    int line;
} Scanner;

// The scanner struct this file will operate on.
static Scanner scanner;

// This is called from external source files before they begin 
// calling scanToken(). Think of it like a constructor.
void initScanner(const char* source) {
    scanner.source      = source;
    scanner.lexemeStart  = source;
    scanner.current     = source;
    scanner.line        = 1;    
}

// This is the only interface (other than initScanner) that the
// use code will ever call. All the lexing stuff is completely
// transparent to the caller of scanToken().
Token scanToken() {
    skipWhitespace();

    scanner.lexemeStart = scanner.current;

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

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.lexemeStart;
    token.length = (int) (scanner.current - scanner.lexemeStart);
    token.line = scanner.line;

    return token;
}
