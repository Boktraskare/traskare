// Code for the expressions used in the parser





static Expr binary(Expr left, Token token, Expr right) {
	binary.left = left;
	binary.token = token;
	binary.right = right;

}


