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
  const char* err;
  Token t;
  Value* value;
  Node*  lc;
  Node*  rc;
} Node;

typedef struct {
  int error;
  Node* root;
} Ast;

Node* consNode(Node*, Value*, Node*);
Node* consErrorNode(const char*, Token);
Value* ttov(Token);
bool freeAst(Node*);
void reportErrors(Node*);
void printAst(Node*);
void printNodeParens(Node*);
void printNode(Node*);
void printValue(Value*);
void printOp(Value*);
void printNum(Value*);

#endif
