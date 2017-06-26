#include "scanner.h"
#include "token.h"

/* ----------------------------------------------------------

   PARSER COMPILER

   This is a recursive descent parser, starting with the top
   rule in the grammar, reading a sentence of tokens from left
   to right while doing leftmost derivation. This means that we
   always choose the leftmost non-terminal to apply a production
   rule to. This means that in the following expression

                            1 + 1
  
   we will recognize the "binary expression" production before
   expanding said production (left to right) into its operands.
   Note that at the outset, the current state of the parser is
   at some root node in the AST sometimes called just "program".
   No matter what the next token actually is we will create a
   node for the production rule which is just under the root
   rule, which probably will be "binary expression", after that
   we'll check for the operands, which will be terminals.

   TODO: Create outline for a parser to handle 1 + 1

   ---------------------------------------------------------- */

// Define the structure for the Parser
// Should it be like this or a list?
typedef struct {
	
	Token current;
	Token previous;

} Parser

// Parse
static Expr parse(){
	return expression();

}


static Expr expression() {
	return assignment(); 
}

static Expr assignment(){
	Expr expr = or();
	return or();
}

static Expr or(){
	Expr expr = and();
	return and();

}

static Expr and(){
	Expr expr = equality();
	return expr;
}

static Expr equality() {
	Expr expr = comparison();
	return expr;
}


static Expr comparison(){
	Expr expr = term();
	return expr;
}

//What to do at term level
static Expr term(){
	Expr expr = factor();
	
	while (match(MINUS, PLUS)){
	Token operator = previous;
	Expr right = factor();
	expr = new Expr.Binary(expr, operator, right);
	}
	return expr;
}

static Expr factor(){
	Expr expr = unary();
	return expr;
}

static Expr unary(){
	return call();
}

static Expr call(){
	Expr expr = primary();

	return expr;
}

//What to do at the primary level for number and strings
static Expr primary(){
	if(match(NUMBER, STRING)) {
        return new Expr.Literal(previous().literal);
        }
}

static bool match(TokenType... types){
	for (TokenType type : types){
		if(check(type)){
		advance();
		return true;
		}
	
	}
	return false;
}

//Check which type of token
static bool check(Tokentype type){
	if(end()) return false;
	return peek().type == type;
}

//Advance the parser
static Token advance(){
	if(!end()) current++;
	return previous();
}

//Check if the parser is at the end
static bool end(){
	return peek().type == EOF;
}

//Return on which token the parser currently are
static Token peek(){
	return parser.current;
}

//Return the previous token
static Token previous(){
	return parser.previous;
}

