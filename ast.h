/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

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

typedef struct {
    Value* value;
    Node*  lc;
    Node*  rc;
} Node;

#endif
