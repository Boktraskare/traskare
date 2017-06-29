/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

   This file contains everything related to the construction
   of AST nodes. The nodes are allocated on the heap. The caller
   will have to do the job of constructing a tree out of the
   nodes returned.

   TODO: Implement function to print the tree, showing nesting
         with parenthesis.

   ---------------------------------------------------------- */

#include <stdlib.h>

#include "ast.h"

// Allocate memory for and construct a Value with the specified
// operator. Return a pointer to this constructed Value on the
// heap. This will later become part of a Node.
Value* consOp(Operator op) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = OPERATOR;
    v->content.op = op;

    return v;
}

// Allocate memory for and construct a Value with the specified
// number value. Return a pointer to this constructed Value on 
// the heap. This will later become part of a Node. Note that
// having long long here means that a number is internally
// represented by a long long.
Value* consNum(long long val) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = NUMBER;
    v->content.value = val;

    return v;
}
