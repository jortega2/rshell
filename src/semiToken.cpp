#include "../header/semiToken.hpp"

SemiToken::SemiToken(Token * l, Token * r){
	left = l;
	right = r;
}

SemiToken::SemiToken(){
	left = nullptr;
	right = nullptr;
}

void SemiToken::setLeft(Token * l){
        left = l;
}

void SemiToken::setRight(Token * r){
        right = r;
}

int SemiToken::execute(){
	if (left == nullptr || right == nullptr){
		ret = 0;
	} else {
		left->execute();
		ret = right->execute();
	}
	return ret;
}
