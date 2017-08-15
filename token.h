/* ----------------------------------------------------------

   TOKEN HEADER

   The lexeme is the word as it appeared in the source, as a
   string. The syntactic category is the classification of
   the word (like noun or verb in regular languages).

   "Syntactic category" is abbreviated "syncat" throughout the
   code. And the SC_ prefix just indicates that the enum is a
   syntactic category.
   
   TODO: Add a string representation of the syntactic category
   to the token.

   ---------------------------------------------------------- */

#ifndef token_h
#define token_h

typedef enum {
  SC_NUM,
  SC_ADD,
  SC_SUB,
  SC_MUL,
  SC_DIV,
  SC_LPR,
  SC_RPR,
  SC_EOF,
  SC_UKN,
} Syncat;

typedef struct {
  const char* start;
  int length;
} Lexeme;

typedef struct {
  Syncat syncat;
  Lexeme lexeme;
  int    lineNumber;
  int    col;
} Token;

#endif
