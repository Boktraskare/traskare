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
  n->lc = lc;
  n->rc = rc;
  return n;
}

Node* consErrorNode(const char* s, Token t) {
  Value* v = malloc(sizeof(Value));
  v->type = ERROR;
  Node* n = consNode(NULL, v, NULL);
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
  v->op = op;
  return v;
}

static Value* consNumVal(long long val) {
  Value* v = malloc(sizeof(Value));
  if (!v) { return NULL; }
  v->type = NUMBER;
  v->number = val;
  return v;
}

void reportErrors(Node* n) {
  if (!n) { return; };
  if (n->err) { printf("%s on %d:%d\n",n->err, n->t.lineNumber, n->t.col); }
  reportErrors(n->lc);
  reportErrors(n->rc);
}

bool freeAst(Node* n) {
  return false;
}

bool expr(Node* n) { return n->lc || n->rc; }

void printAst(Node* n) {
  printNodeParens(n);
}

void printNodeParens(Node* n) {
  printf("(");
  printValue(n->value);
  putchar(' ');
  printNode(n->lc);
  putchar(' ');
  printNode(n->rc);
  printf(")");
}

void printNode(Node* n) {
  if (!n) { return; };
  switch (n->value->type) {
    case OPERATOR: printNodeParens(n); break;
    case NUMBER: printValue(n->value); break;
    case ERROR: printErrorNode(n); break;
  }
}

void printValue(Value* v) {
  switch (v->type) {
    case OPERATOR: printOp(v); break;
    case NUMBER: printNum(v); break;
  }
}

void printOp(Value* v) {
  switch(v->op) {
    case OP_ADD: putchar('+'); break;
    case OP_SUB: putchar('-'); break;
    case OP_MUL: putchar('*'); break;
    case OP_DIV: putchar('/'); break;
  }
}

void printNum(Value* v) {
  printf("%llu", v->number);
}

void printErrorNode(Node* n) {
  printf("%s", n->err);
}
