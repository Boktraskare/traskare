// Code for the expressions used in the parser
// Not sure if all expressions should be defined in a header or if this file is needed




static Expr binary(Expr left, Token token, Expr right) {
	binary.left = left;
	binary.token = token;
	binary.right = right;

}


