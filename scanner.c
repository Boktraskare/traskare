#include "scanner.h"

/* ----------------------------------------------------------

                          SCANNER

This file will be #included by the parser.c file. The parser
can then initialize the scanner with the source code and call
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

// Global scanner object.
Scanner scanner;

void initScanner(const char* source) {
    scanner.source      = source;
    scanner.lexemeStart = source;
    scanner.current     = source;
    scanner.line        = 1;    
}
