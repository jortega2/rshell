#include "../header/semiToken.hpp"

SemiToken::SemiToken(Token * l, Token * r){
	left = l;
	right = r;
}

SemiToken::SemiToken(){
	left = nullptr;
	right = nullptr;
}

std::string SemiToken::stringify(){
	if (left != nullptr && right != nullptr){
	        return left->stringify() + " ; " + right->stringify();
	} else {
		return "\0";
	}
}


void SemiToken::setLeft(Token * l){
        left = l;
}

void SemiToken::setRight(Token * r){
        right = r;
}

Token* SemiToken::getLeft(){
        return left;
}

Token* SemiToken::getRight(){
        return right;
}

int SemiToken::isLeaf(){
	return 0;
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
