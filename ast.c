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
#include "token.h"

static Value* consOpVal(Operator op);
static Value* consNumVal(long long val);

Node* consNode(Node* lc, Value* v, Node* rc) {
  Node* n = malloc(sizeof(Node));
  n->value = v;
  n->lc    = lc;
  n->rc    = rc;
  return n;
}

Node* consErrorNode(const char* s, Token t) {
  Node* n = malloc(sizeof(Node));
  n->err = s;
  n->t = t;
  return n;
}

Value* ttov(Token t) {
  switch(t.syncat) {
    case SC_ADD: return consOpVal(OP_ADD); break;
    case SC_SUB: return consOpVal(OP_SUB); break;
    case SC_MUL: return consOpVal(OP_MUL); break;
    case SC_DIV: return consOpVal(OP_DIV); break;
    case SC_NUM:
      return consNumVal(strtoll(t.lexeme.start, NULL, 10));
      break;
    case SC_EOF:
    case SC_UKN:
      return NULL;
  }

  return NULL; // TODO (Error handling): What to do here?
}

static Value* consOpVal(Operator op) {
  Value* v = malloc(sizeof(Value));
  if (!v) { return NULL; }
  v->type = OPERATOR;
  v->content.op = op;
  return v;
}

static Value* consNumVal(long long val) {
  Value* v = malloc(sizeof(Value));
  if (!v) { return NULL; }
  v->type = NUMBER;
  v->content.number = val;
  return v;
}

void reportErrors(Node* n) {
  if (n == NULL) { return; };
  if (n->err) {printf("%s on %d:%d\n",n->err, n->t.lineNumber, n->t.col);}
  reportErrors(n->lc);
  reportErrors(n->rc);
}

bool freeAst(Node* ast) {
  return false;
}

bool expr(Node* n) { return n->lc || n->rc; }

void printAst(Node* n) {
  if (!n) { return; }
  if (expr(n)) {
    printNodeParens(n);
  } else {
    printNode(n);
  }
}

void printNodeParens(Node* n) {
  printf("(");
  printNode(n);
  printf(")");
}

void printNode(Node* n) {
  printValue(n->value);
  printAst(n->lc);
  printAst(n->rc);
}

void printValue(Value* v) {
  switch (v->type) {
    case OPERATOR:
      printOp(v->content.op);
      break;
    case NUMBER:
      printNumber(v->content.number);
      break;
  }
}

void printOp(Operator op) {
  switch (op) {
    case OP_ADD:
      putchar('+');
      break;
    case OP_SUB:
      putchar('-');
      break;
    case OP_MUL:
      putchar('*');
      break;
    case OP_DIV:
      putchar('/');
      break;
  }
}

void printNumber(long long n) {
  printf("%llu", n);
}
