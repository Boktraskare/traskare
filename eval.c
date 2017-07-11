/* ----------------------------------------------------------

   EVALUATION OF AST
   
   This file contains what is needed to evaluate expressions.

   To evaluate expressions we do something very much like the
   printing of the AST. We traverse the tree in pre-order, but
   instead of just printing the node, we pass it to the appropriate
   function or operator in the implementation language (C).
   
   ---------------------------------------------------------- */
/*
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "eval.h"
#include "ast.h"

// TODO: Move all printing of Values here.
// #include "print.h"

static long long binary(Node*);

void eval(Node* ast) {
    switch(ast->value->type) {
    case OPERATOR:
        binary(ast);
        break;
    case NUMBER:
        ast->value.content.number;
        break;
    }
}

static long long binary(Node* ast) {
    Value* lc = eval(ast->lc);
    Value* rc = eval(ast->rc);

    switch(ast->value->content.op) 
        case OP_ADD: return lc + rc;
        case OP_SUB: return lc - rc;
        case OP_MUL: return lc * rc;
        case OP_DIV: return lc / rc;    
    }

    return NULL;
}




 
*/
