/* ----------------------------------------------------------

   TOKEN

   This file contains some helpers for inspecting tokens. Most
   of the things related to tokens are declarations and are
   found in token.h.

   ---------------------------------------------------------- */

#include "token.h"

typedef struct {
    Syncat syncat;
    const char* string;
} SyncatToString;

static SyncatToString syncatToString[] = {
    {SC_NUM, "SC_NUM"}, 
    {SC_ADD, "SC_ADD"}, 
    {SC_EOF, "SC_EOF"}, 
    {SC_ERR, "SC_ERR"}, 
};

// Convert a syntactic category to it's string representation
const char* cattostr(Syncat syncat) {
    SyncatToString* table = syncatToString;
    SyncatToString* end = table + sizeof(syncatToString)/sizeof(syncatToString[0]);

    while (table < end) {
        if (table->syncat == syncat) {
            return table->string;
        }

        table++;
    }

    return "NO_STRING_REPRESENTATION";
}
