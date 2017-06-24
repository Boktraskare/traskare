/* ----------------------------------------------------------

   TOKEN

   This file contains some helpers for inspecting tokens. Most
   of the things related to tokens are declarations and are
   found in token.h.

   ---------------------------------------------------------- */

#include "token.h"

TokenToString tokenToString[] = {
    {TOKEN_NUMBER, "TOKEN_NUMBER"}, 
    {TOKEN_PLUS,   "TOKEN_PLUS"}, 
    {TOKEN_EOF,    "TOKEN_EOF"}, 
    {TOKEN_ERROR,  "TOKEN_ERROR"}, 
};

// Convert a token type to it's string representation.
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
