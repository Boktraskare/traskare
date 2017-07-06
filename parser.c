/* ----------------------------------------------------------

   RECURSIVE DESCENT PARSER

   The input to the parser is the stream of tokens which the
   parser will consume at will, a token at a time. The output
   is the abstract syntax tree (AST).

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
static bool maa(TokenType);

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
    
    while (maa(TOKEN_PLUS) || maa(TOKEN_MINUS)) {
        Value* val = tokenToValue(parser.previous);
        Node* n = consNode(ast, val, factor());        
        ast = n;
    }

    return ast;
}

static Node* factor() {
    Node* ast = primary();

    while (maa(TOKEN_MUL) || maa(TOKEN_DIV)) {
        Value* val = tokenToValue(parser.previous);
        Node* n = consNode(ast, val, primary());
        ast = n;
    }

    return ast;
}

static Node* primary() {
    if (maa(TOKEN_NUMBER)) {
        Value* val = tokenToValue(parser.previous);
        Node* n = consNode(NULL, val, NULL);
        return n;
    }

   error(); // TODO (Error handling): What to do here?
   return false; // very temporary fix
}

// Match and Advance
static bool maa(TokenType t) {
    if (match(t)) {
        advance();
        return true;
    }
   
   return false;
}

static bool match(TokenType t) {
    return parser.current.type == t;
}

static void advance() {
    parser.previous = parser.current;
    parser.current = scanToken();
}

// TODO: How to handle errors?
static void error() {
    exit(1);
}
