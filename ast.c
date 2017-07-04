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
#include <stdbool.h>
#include <stdio.h>

#include "ast.h"

static void paren(char*, Node*);
static bool literal(Node*);

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

void printValue(Node*);
void printExpr(Node*);
void printOp(Operator);

/*

    +
 1     *
     2   3

*/
// Print the AST. This is used for debugging only.
// TODO: Put the string representation of the Value straight into struct?
void printAst(Node* ast) {
    printValue(ast);

    if (ast->lc != NULL) {
        printAst(ast);
    }

    if (ast->rc != NULL) {
        printAst(ast);
    }
}

void printExpr(Node* ast) {
    printAst(ast);
}

void printValue(Node* ast) {
    switch(ast->value->type) {
        case OPERATOR:
            printOp(ast->value->content.op);
            break;
        case NUMBER:
            printf("%llu", ast->value->content.value);
            break;
    }
}

void printOp(Operator op) {
    switch(op) {
        case OP_SUB:
            printf("-");
            break;
        case OP_ADD:
            printf("+");
            break;
        case OP_MUL:
            printf("*");
            break;
        case OP_DIV:
            printf("/");
            break;
    }
}
