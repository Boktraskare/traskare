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

static Parser* parser;

void initParser() {
    parser->current  = scanToken();
    parser->previous = parser->current;
}

// This function kicks of the whole recursive descent. It's the
// only function the use code has to call.
Node* parse() {
    if (!parser) {
        error();
    }

    // Go into recursive descent and return the result.
    return expression();
}

static Node* expression() {
    return term(); 
}

/* 

   term -> factor (("-" | "+") factor)*
 
   The evolution of the AST visualized. Note that leftChild and
   rightChild might extend a complete tree themselves, but we
   connect both of them with a completely new and unconnected
   operator node
  
   1.              (ast)
  
   2.           (leftChild)
  
   3.       (leftChild) (parent)
  
   4.(leftChild) (parent) (rightChild)
  
   5.            (parent)
   /        \
   (leftChild)          (rightChild)
  
   5.            (ast)
   /     \
   (leftChild)       (rightChild)
   
*/  
static Node* term() {   
    Node* ast = factor(); // 1.
    
    while (match(TOKEN_PLUS) || match(TOKEN_MINUS)) {
        advance();

        Node* leftChild = ast; // 2.

        // 3.
        Value* op;
        switch (parser->previous.type) {
        case TOKEN_PLUS:
            op = consOp(OP_ADD);
            break;
        case TOKEN_MINUS:
            op = consOp(OP_SUB);
            break;
        default:
            error();
        }
        Node* parent = malloc(sizeof(Node));
        
        Node* rightChild = factor(); // 4.

        // 5.
        parent->value = op;
        parent->lc = leftChild;
        parent->rc = rightChild;
        
        ast = parent; // 6.
    }

    return ast;
}

/* 

   factor -> primary (("*" | "/") primary)*
   
*/
static Node* factor() {
    Node* ast = primary();

    while (match(TOKEN_MUL) || match(TOKEN_DIV)) {
        advance();

        Value* op;
        switch (parser->previous.type) {
        case TOKEN_MUL:
            op = consOp(OP_MUL);
            break;
        case TOKEN_DIV:
            op = consOp(OP_DIV);
            break;
        default:
            error();
        }
        Node* parent = malloc(sizeof(Node));
        
        Node* rightChild = primary();

        parent->value = op;
        parent->lc = ast;
        parent->rc = rightChild;

        ast = parent;
    }

    return ast;
}

/* 

   primary -> NUM
   
*/
static Node* primary() {
    if (match(TOKEN_NUMBER)) {
        advance();
       
        // Convert lexeme of type string to type long long.
        char* lexemeStart = parser->previous.start;
        long long num = strtoll(lexemeStart, NULL, 10);
       
        Node* prim = malloc(sizeof(Node));
       
        prim->value = consNum(num);       
        prim->lc = NULL;
        prim->rc = NULL;
       
        return prim;
    }

   // Last stop.
   error();
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
    return parser->current.type == t;
}

static void advance() {
    parser->previous = parser->current;
    parser->current = scanToken();
}

// TODO: How to handle errors?
static void error() {
    exit(1);
}
