#include "../header/orToken.hpp"

OrToken::OrToken(Token * l, Token * r){
	left = l;
	right = r;
}

OrToken::OrToken(){
	left = nullptr;
	right = nullptr;
}

void OrToken::setLeft(Token * l){
        left = l;
}

void OrToken::setRight(Token * r){
        right = r;
}

Token* OrToken::getLeft(){
        return left;
}

Token* OrToken::getRight(){
        return right;
}

int OrToken::isLeaf(){
	return 0;
}

int OrToken::execute(){
	if (left == nullptr | right == nullptr ){
		ret = 0;
	}else if (left->execute() == 0){
		if (right ->execute() == 1){
			ret = 1;
		}
		else {	
			ret = 0;
		}
	} else {
		ret = 1;
	}
	return ret;
};
