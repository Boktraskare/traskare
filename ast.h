/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE HEADER

   Typedefs and enumerations related to the AST.

   ---------------------------------------------------------- */

#ifndef ast_h
#define ast_h


// Indicates what type of operator is contained in an OPERATOR
// ValueType.
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
} Operator;

// Union tag.
typedef enum {
    OPERATOR,
    NUMBER,
} ValueType;

// A tagged union. The union can hold any of its members. The
// tag indicates which one it is so we know how to read its
// value.
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

Value* consOp(Operator);
Value* consNum(long long);
void printAst(Node*);

#endif
