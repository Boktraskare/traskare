/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE HEADER

   Typedefs and enumerations related to the AST.

   ---------------------------------------------------------- */

#ifndef ast_h
#define ast_h

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
        long long value;
    } content;
} Value;

typedef struct Node Node;
typedef struct Node {
    Value* value;
    Node*  lc;
    Node*  rc;
} Node;

Node* consNode(Node*, Value*, Node*)
Value* tokenToValue(Token);
void printAst(Node*);

#endif
