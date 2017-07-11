/* ----------------------------------------------------------

   SCANNER

   The only interface to the scanner is simply the scanToken()
   function. This means that the lexer analyses the source for 
   tokens "on demand". No list of tokens is ever buffered. This 
   detail is completely transparent to the parser. This saves
   us from having to buffer a list of tokens between the scanner
   and the parser.

   To understand everything that goes on in the scanner you
   should have a look at the token implementation.

   ---------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"
#include "token.h"

static bool end();
static void skipWhitespace();
static char peekNext();
static Token number();
static bool isAtEnd();
static char peek();
static bool isDigit(char c);
static char advance();
static Token makeToken(Syncat);

typedef struct {
    const char* source;
    const char* lexemeStart;
    const char* current;
    int line;
} Scanner;

static Scanner scanner;

void initScanner(const char* source) {
    scanner.source      = source;
    scanner.lexemeStart = source;
    scanner.current     = source;
    scanner.line        = 1;    
}

Token scanToken() {
    skipWhitespace();

    scanner.lexemeStart = scanner.current;

    if (*scanner.current == '\0') {
        return makeToken(SC_EOF);
    }

    char c = advance();

    switch (c) {
        case '+': return makeToken(SC_ADD); break;
        case '-': return makeToken(SC_SUB); break;
        case '*': return makeToken(SC_MUL); break;
        case '/': return makeToken(SC_DIV); break;
        default:
            if(isDigit(c)) {
                return number();
            }
    }

    return makeToken(SC_ERR); // TODO (Error handling): What to do here?
}

static Token makeToken(Syncat syncat) {
    Token token;
    token.syncat = syncat;
    token.lexeme.start = scanner.lexemeStart;
    token.lexeme.length = (int) (scanner.current - scanner.lexemeStart);
    token.lineNumber = scanner.line;
    return token;
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

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

static char peek() {
    return *scanner.current;
}

static Token number() {
    while (isDigit(peek())) advance();
    return makeToken(SC_NUM);
}
