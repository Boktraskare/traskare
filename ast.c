/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

   This file contains everything related to the construction of
   AST nodes and their value.
   
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ast.h"

static void printValue(Node*);
static void printExpr(Node*);
static void printOp(Operator);
Value* consOpVal(Operator op)
Value* consNumVal(long long val)

Value* consOpVal(Operator op) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = OPERATOR;
    v->content.op = op;

    return v;
}

Value* consNumVal(long long val) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = NUMBER;
    v->content.value = val;

    return v;
}

Node* consNode(Node* lc, Value* v, Node* rc) {
    Node* n = malloc(sizeof(Node));
   
    n->value = v;
    n->lc    = lc;
    n->rc    = rc;
}

/* ----------------------------------------------------------

   Everything that follows is related to the printing of the 
   ast. Might be better to move this to another file.

   Give this function an ast, and it will print it in prefix 
   notation. A tree such as the one below will be printed in 
   pre order as (+ 1 (* 2 3)).

       +
    1     *
        2   3
     
   TODO: Make sure it works.

   ---------------------------------------------------------- */
void printAst(Node* ast) {
    printValue(ast);

    if (ast->lc != NULL) {
        printAst(ast);
    }

    if (ast->rc != NULL) {
        printAst(ast);
    }
}

static void printValue(Node* ast) {
    switch(ast->value->type) {
        case OPERATOR:
            printOp(ast->value->content.op);
            break;
        case NUMBER:
            printf("%llu", ast->value->content.value);
            break;
    }
}

static void printOp(Operator op) {
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
