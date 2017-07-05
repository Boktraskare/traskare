/*
 *  
 *
 *  This file contains what is needed to evaluate expressions.
 *
 *  Need a function for parentheses and for binary expressions 
 *
 *
 *
 */

#include "eval.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

long long binary(Node* ast);


//Evaluating binary expressions of numbers and simple math
long long binary(Node* ast){
    long long right = ast->rc->value->content.value;
    long long left = ast->lc->value->content.value;

    switch(ast->value->content.op){
        case OP_ADD:
            return (long long) left + (long long) right;

        case OP_SUB:
            return (long long) left - (long long) right;

        case OP_MUL:
            return (long long) left * (long long) right;

        case OP_DIV:
            return (long long) left / (long long) right;
    
    }

    return false; //Very temporary
}




 
