/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

   ---------------------------------------------------------- */

#include "ast.h"

Value* consOp(Operator op) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = OPERATOR;
    v->content.op = op;

    return v;
}

Value* consNum(long long val) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = NUMBER;
    v->content.op = op;

    return v;
}
