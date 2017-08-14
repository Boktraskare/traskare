/* ----------------------------------------------------------

   ABSTRACT SYNTAX TREE

   This file contains everything related to the construction of
   AST nodes and their value.

   consNode() and tokenToValue() are the only functions needed
   to construct nodes for the AST. These functions are called
   by the parser.

   TODO: Implement freeAst
   TODO: Implement reportErrors
   
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ast.h"

static Value* consOpVal(Operator op);
static Value* consNumVal(long long val);

Node* consNode(Node* lc, Value* v, Node* rc) {
  Node* n = malloc(sizeof(Node));
  n->value = v;
  n->lc    = lc;
  n->rc    = rc;
  return n;
}

Node* consErrorNode(const char* s) {
  Node* n = malloc(sizeof(Node));
  n->err = s;
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
          
      // TODO (Error handling): How to handle these?
    case SC_EOF:
    case SC_UKN:
      return NULL;
  }

  return NULL; // TODO (Error handling): What to do here?
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
  v->content.number = val;

  return v;
}

bool freeAst(Node* ast) {
  return false;
}

void reportErrors(Ast ast) {
  // Print errors to the user.
}
