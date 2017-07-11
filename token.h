/* ----------------------------------------------------------

   TOKEN HEADER

   A token is lexeme, the syntactic category for that lexme,
   and the line number it appeared on. All a "token" really is
   then is the source text, divided into it's words and some
   metadata on those words.

   The lexeme is the word as it appeared in the source, as a
   string. The syntactic category is the classification of
   the word (like noun or verb in regular languages).

   ---------------------------------------------------------- */

#ifndef token_h
#define token_h

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
