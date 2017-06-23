#include "scanner.h"

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


// Scan for token and switch into the correct case with the default case being numbers
static void scanToken(){
        char c = advance();
        switch (c) {
                case '+': makeToken(PLUS); break;

        default:
                if(isdigit(c)){
                        number();
                }
        }
}

static Token makeToken(TokenType type) {
	Token token;
	token.type = type;
	token.star = scanner.tokenStart;
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
        return scanner.current[1];
}

// Look at the current character
static char peek() {
	return *scanner.current;
}

// Check if the scanner is at the end
static bool isAtEnd() {
	return *scanner.current == '\0';
}

// Check the next character
static char peekNext() {
	if(isAtEnd()) return '\0';
	return scanner.current[1];
}

// What to do if the character is a number
static Token number() {
        while(isDigit(peek())) advance();

        if(peek() == '.' && isDigit(peeknext())) {
        	advance();
	
		while (isDigit(peek())) advance();
       	}
	return makeToken(TOKEN_NUMBER);
}


