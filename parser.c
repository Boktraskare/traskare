/* ----------------------------------------------------------

   RECURSIVE DESCENT PARSER

   The input to the parser is the stream of tokens which the
   parser will consume at will, a token at a time. The output
   is the abstract syntax tree (AST).

   In this file we  look at the syntactic category of the
   current token to figure out how it should be parsed. See
   token.h for more info on the implementation of tokens.

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
    Token current;
    Token previous;
    Node* ast;
} Parser;

static Node* primary();
static Node* expression();
static Node* term();
static bool maa(Syncat);

static Parser parser;

void initParser() {
    parser.current  = scanToken();
    parser.previous = parser.current;
}

Node* parse() {
    return expression();
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

    error(); // TODO (Error handling): What to do here?
    return false; // very temporary fix
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

// TODO: How to handle errors?
static void error() {
    exit(1);
}
