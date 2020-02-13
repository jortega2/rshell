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
	int ret;

	if (right == NULL){
		ret = left->execute();
	}
	
	if (right != NULL){
		left->execute();
		ret = right->execute();
	}
	return ret;
}
