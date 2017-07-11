#ifndef token_h
#define token_h

/* ----------------------------------------------------------

   TOKEN HEADER

   This file contains every declaration needed to handle tokems.

   ---------------------------------------------------------- */

// Syntactic categories (token types).
typedef enum {
    SC_NUM,
    SC_ADD,
    SC_SUB,
    SC_MUL,
    SC_DIV,
    SC_EOF,
    SC_ERR,
} Syncat;

typedef struct {
    const char* start;
    int length;
} Lexeme;

typedef struct {
    Syncat syncat;
    Lexeme lexeme;
    int    lineNumber;
} Token;

const char* cattostr(Syncat syncat);

#endif
