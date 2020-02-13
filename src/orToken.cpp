#include "../header/orToken.hpp"

OrToken::OrToken(Token * a, Token * b){
	left = a;
	right = b;
}
int OrToken::execute(){
	if(left->execute() == 0){
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
