#include "../header/andToken.hpp"

AndToken::AndToken(Token * l, Token * r){
	left = l;
	right = r;
}

AndToken::AndToken() {
	left = nullptr;
	right = nullptr;
}

std::string AndToken::stringify(){
	if ( right != nullptr && left != nullptr){
	        return left->stringify() + " && " + right->stringify();
	} else {
		return "\0";
	}
}


void AndToken::setLeft(Token * l){
	left = l;
}

void AndToken::setRight(Token * r){
        right = r;
}

Token* AndToken::getLeft(){
	return left;
}

Token* AndToken::getRight(){
	return right;
}

int AndToken::isLeaf(){
	return 0;
}

int AndToken::execute(){
	if (left == nullptr || right == nullptr){
		ret = 0;
	} else if(left->execute() == 1){
		if (right ->execute() == 1){
			ret = 1;
		}
		else {	
			ret = 0;
		}
	} else {
		ret = 0;
	}
	return ret;
};
