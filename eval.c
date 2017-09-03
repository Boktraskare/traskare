/* ----------------------------------------------------------

   EVALUATION OF AST
   
   This file contains what is needed to evaluate expressions.

   To evaluate expressions we do something very much like the
   printing of the AST. We traverse the tree in pre-order, but
   instead of just printing the node, we pass it to the appropriate
   function or operator in the implementation language (C).
   
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "eval.h"
#include "ast.h"

static long long binary(Node*);

long long eval(Node* ast) {
    switch(ast->value->type) {
        case OPERATOR: return binary(ast); break;
        case NUMBER: return ast->value->number; break;
    }

    printf("Error in evaluation");
    return -1337; // TODO (error handling)
}

static long long binary(Node* ast) {
    Node* lc = ast->lc;
    Node* rc = ast->rc;
    
    switch(ast->value->op) {
        case OP_ADD: return eval(lc) + eval(rc); break;
        case OP_SUB: return eval(lc) - eval(rc); break;
        case OP_MUL: return eval(lc) * eval(rc); break;
        case OP_DIV: return eval(lc) / eval(rc); break;
    }

    return -1337; // TODO (error handling)
}
