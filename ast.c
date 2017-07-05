/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

   This file contains everything related to the construction of
   AST nodes and their value.

   consNode() and tokenToValue() are the only functions needed
   to construct nodes for the AST. These functions are called
   by the parser.
   
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ast.h"

static void printValue(Node*);
static void printExpr(Node*);
static void printOp(Operator);
static Value* consOpVal(Operator op);
static Value* consNumVal(long long val);
static bool expr(Node*);
void printParenthesized(Node*);

Node* consNode(Node* lc, Value* v, Node* rc) {
    Node* n = malloc(sizeof(Node));
   
    n->value = v;
    n->lc    = lc;
    n->rc    = rc;

    return n;
}

// The parser works on a stream of tokens, and a token is nothing more
// than a TokenType and a string lexeme. We must convert these values
// to the types of the implementation language (C in this case). This
// is where our source code turns into C.
Value* tokenToValue(Token t) {
    switch(t.type) {
    case TOKEN_NUMBER: return consNumVal(strtoll(t.start, NULL, 10)); break;
    case TOKEN_PLUS:   return consOpVal(OP_ADD); break;
    case TOKEN_MINUS:  return consOpVal(OP_SUB); break;
    case TOKEN_MUL:    return consOpVal(OP_MUL); break;
    case TOKEN_DIV:    return consOpVal(OP_DIV); break;
    case TOKEN_EOF:
    case TOKEN_ERROR:
        return NULL;
    }

    return NULL;
}

static Value* consOpVal(Operator op) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = OPERATOR;
    v->content.op = op;

    return v;
}

static Value* consNumVal(long long val) {
    Value* v = malloc(sizeof(Value));

    if (!v) {
        return NULL;
    }

    v->type = NUMBER;
    v->content.value = val;

    return v;
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
    if (ast == NULL) {
        return;
    }
   
    if (expr(ast)) {
        printParenthesized(ast);
    } else {
        printValue(ast);
    }
}

void printParenthesized(Node* ast) {
    printf("(");
    printValue(ast);
    printf(" ");
    printAst(ast->lc);
    printf(" ");
    printAst(ast->rc);
    printf(")");
}

static bool expr(Node* ast) {
    return (ast->lc != NULL || ast->rc != NULL);
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
