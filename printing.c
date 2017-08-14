/* ----------------------------------------------------------

   PRINTING

   This file contains utilities for printing various data
   structures in the interpreter. These utilities can be used
   for debugging, but are also used when printing the output
   of a program.

   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "token.h"
#include "printing.h"

static bool expr(Node*);
static void printParenthesized(Node*);
static void printValue(Node*);
static void printExpr(Node*);
static void printOp(Operator);

// Print a syntactic category as a string.
const char* cattostr(Syncat syncat) {
  const SyncatToString* table = syncatToString;
  int n = sizeof(syncatToString)/sizeof(syncatToString[0]);
  const SyncatToString* end = table + n;

  while (table < end) {
    if (table->syncat == syncat) {
      return table->string;
    }

    table++;
  }

  return "NO_STRING_REPRESENTATION";
}

// Give this function an ast, and it will print it in prefix 
// notation. A tree such as the one below will be printed in 
// pre order as (+ 1 (* 2 3)).
//
//     +
//  1     *
//      2   3
//
void printAst(Node* node) {
  if (node == NULL) { return; }
  if (expr(node)) {
    printParenthesized(node);
  } else {
    printValue(node);
  }
}

static void printParenthesized(Node* node) {
  printf("(");
  printValue(node);
  printf(" ");
  printAst(node->lc);
  printf(" ");
  printAst(node->rc);
  printf(")");
}

static bool expr(Node* node) {
  return (node->lc != NULL || node->rc != NULL);
}

static void printValue(Node* node) {
  if (node->err) {
    printf("%s", node->err);
    return;
  }
  
  switch(node->value->type) {
    case OPERATOR:
      printOp(node->value->content.op);
      break;
    case NUMBER:
      printf("%llu", node->value->content.number);
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
