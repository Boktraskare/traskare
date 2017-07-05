/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE HEADER

   Typedefs and enumerations related to the AST.

   ---------------------------------------------------------- */

#ifndef ast_h
#define ast_h

#include "token.h"

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
} Operator;

typedef enum {
    OPERATOR,
    NUMBER,
} ValueType;

// This struct is essentially the most atomic part of the whole
// interpreter. When evaluating the AST, all we have to work on
// are structs like this one.
//
// Currently only operators and numbers are allowed. Eventually
// the union will also contain strings and keywords etc.
typedef struct {
    ValueType type;   
    union {
        Operator  op;
        long long value; // TODO: rename this to "number"
    } content;
} Value;

typedef struct Node Node;
typedef struct Node {
    Value* value;
    Node*  lc;
    Node*  rc;
} Node;

Node* consNode(Node*, Value*, Node*);
Value* tokenToValue(Token);
void printAst(Node*);

#endif
