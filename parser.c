/* ----------------------------------------------------------

   PARSER COMPILER

   

   ---------------------------------------------------------- */
 

typedef struct {
	
	Token current;
	Token previous;

} Parser

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

static Expr primary(){
	
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

static bool check(Tokentype type){
	if(end()) return false;
	return peek().type == type;
}

static Token advance(){
	if(!end()) current++;
	return previous();
}

static bool end(){
	return peek().type == EOF;
}

static Token peek(){
	return parser.current;
}

static Token previous(){
	return parser.previous;
}




}
