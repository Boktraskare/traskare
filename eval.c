/* ----------------------------------------------------------

   EVALUATION OF AST
   
   This file contains what is needed to evaluate expressions.
   
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "eval.h"

long long binary(Node*);

// Evaluating binary expressions of numbers and simple math
long long binary(Node* ast) {
   
    // TODO: These needs to be evaluated recursively
    long long right = ast->rc->value->content.value;
    long long left = ast->lc->value->content.value;

    switch(ast->value->content.op) 
        case OP_ADD: return left + right;
        case OP_SUB: return left - right;
        case OP_MUL: return left * right;
        case OP_DIV: return left / right;    
    }

    return false; // Very temporary
}




 
