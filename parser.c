/* ----------------------------------------------------------

   RECURSIVE DESCENT PARSER

   The input to the parser is the stream of tokens which the
   parser will consume at will, a token at a time. The output
   is the abstract syntax tree (AST).

   In the parser we look at the syntactic category of the
   current token and construct the appropriate value. See
   token.h for more info on the implementation of tokens.
   
   TODO: Enter panic mode after error occurs.

   ---------------------------------------------------------- */

#include <stdbool.h>
#include <stdlib.h>

#include "scanner.h"
#include "token.h"
#include "ast.h"

static void error();
static Node* expression();
static Node* term();
static Node* factor();
static bool match();
static void advance();

typedef struct {
  Token current; // Lookahead LL(1)
  Token previous;
  Node* ast;
} Parser;

static Node* primary();
static Node* expression();
static Node* term();
static bool maa(Syncat);
static void setError();

static Parser parser;

void initParser() {
  parser.current  = scanToken();
  parser.previous = parser.current;
}

/*
** error is set whenever the parser can't parse something. This
** flag indicates to the caller of the parser that the returned
** ast is not fit for execution and should be traversed and it's
** errors reported to the user of the program.
*/

static bool errOccurred = false;

Ast parse() {
  Node* root = expression();
  return (Ast) { .error = (errOccurred ? 1 : 0), .root = root };
}

static Node* expression() {
  return term(); 
}

static Node* term() {   
  Node* ast = factor();
    
  while (maa(SC_ADD) || maa(SC_SUB)) {
    Value* val = ttov(parser.previous);
    ast = consNode(ast, val, factor());        
  }

  return ast;
}

static Node* factor() {
  Node* ast = primary();

  while (maa(SC_MUL) || maa(SC_DIV)) {
    Value* val = ttov(parser.previous);
    ast = consNode(ast, val, primary());
  }

  return ast;
}

static Node* primary() {
  if (maa(SC_NUM)) {
    Value* val = ttov(parser.previous);
    return consNode(NULL, val, NULL);
  }

  if (maa(SC_LPR)) {
    Node* ast = expression();
    if (!maa(SC_RPR)) {
      setError();
      return consErrorNode("Errror, expected left paren");
    }
    return ast;
  }

  setError();
  return consErrorNode("Error parsing");
}

// Match and Advance
static bool maa(Syncat syncat) {
  if (match(syncat)) {
    advance();
    return true;
  }
  return false;
}

static bool match(Syncat syncat) {
  return parser.current.syncat == syncat;
}

static void advance() {
  parser.previous = parser.current;
  parser.current = scanToken();
}

static void setError() {
  errOccurred = true;
}
