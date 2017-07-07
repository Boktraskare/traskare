/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE HEADER

   Typedefs and enumerations related to the AST.

   The AST is a simple binary tree, with a Value attached to
   each node. The value is represented by a tagged union. This
   union must grow when the language grows to handle new values
   such as strings and statements.

   The Value struct also shows what types we choose to represent
   the internal values with. For example, we use long long for
   every number Value, and an operator is simply an enumeration
   of Operators.

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

typedef struct {
    ValueType type;   
    union {
        Operator  op;
        long long number;
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
