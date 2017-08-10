
/* ----------------------------------------------------------

   PRINTING HEADER

   ---------------------------------------------------------- */

#ifndef printing_h
#define printing_h

#include "ast.h"

const char* cattostr(Syncat syncat);
void printAst(Node*);

typedef struct {
    Syncat syncat;
    const char* string;
} SyncatToString;

static const SyncatToString syncatToString[] = {
    {SC_NUM, "SC_NUM"}, 
    {SC_ADD, "SC_ADD"}, 
    {SC_EOF, "SC_EOF"}, 
    {SC_UKN, "SC_UKN"}, 
};

#endif
