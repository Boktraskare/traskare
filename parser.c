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

static Parser* parser;

// This function kicks of the whole recursive descent. It's the
// only function the use code has to call.
Node* parse() {
    parser = malloc(sizeof(Parser));

    if (!parser) {
        error();
    }

    return expression();

}

static Node* expression() {
    return term(); 
}

/* term -> factor (("-" | "+") factor)*
 
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
    // 1.
    Node* ast = factor();

    while (match(TOKEN_PLUS) || match(TOKEN_MINUS)) {
        advance();

        // 2.
        // If we get here, we know that the node we parsed above
        // is the left child of an Operator node in the AST. For
        // clarity we now rename that node to indicate this
        // change in perspective.
        Node* leftChild = ast;

        // 3.
        // Now comes the work of constructing the operator node.
        // Note that this is a completely fresh and unconnected
        // node.
        Value* op;
        switch (parser->current.type) {
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

        // 4.
        // Now we continue on parsing the tokens after the PLUS
        // or MINUS token, knowing that it's a right child of
        // the previously created operator token.
        Node* rightChild = factor();

        // 5.
        // Tie it all together and make this new operator node
        // the 
        parent->lc = leftChild;
        parent->value = op;
        parent->rc = rightChild;

        // 6. The parent is the new "top node".
        ast = parent;
    }

    return ast;
}

static Node* factor() {
    return NULL;
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
