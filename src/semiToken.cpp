#include "../header/semiToken.hpp"

SemiToken::SemiToken(Token * l){
	left = l;
	Token *n;
	n = NULL;
	right = n;
}
SemiToken::SemiToken(Token * l, Token * r){
	left = l;
	right = r;
}

int SemiToken::execute(){
	left->execute();
	if (right != NULL){
		right->execute();
	}
	return 1;
}
