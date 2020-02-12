#include "../header/andToken.hpp"

AndToken::AndToken(Token * a, Token * b){
	left = a;
	right = b;
}
int AndToken::execute(){
	if(left->execute() == 1){
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
