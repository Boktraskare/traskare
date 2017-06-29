#ifndef token_h
#define token_h

/* ----------------------------------------------------------

   TOKEN HEADER

   This file contains every declaration needed to handle tokems.

   ---------------------------------------------------------- */

// The different token types currently available. These are just
// enums, and so they have no string representation. To print a
// the name of a token type you have to use ttos (string to
// token).
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EOF,
    TOKEN_ERROR,
} TokenType;

// Every metadata we need about a token is held in a structure
// like this one. Besides having a type, a token knows of the
// specific lexeme in the source which this token was made out
// of.
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

// Just a a helper method to return the token type as a string.
const char* ttos(TokenType type);

#endif
