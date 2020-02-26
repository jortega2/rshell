#ifndef __SEMITOKEN_HPP__
#define __SEMITOKEN_HPP__

#include "Token.hpp"

class SemiToken : public Token {
private:
	Token * left;
	Token * right;
	int ret;
public:
	SemiToken(Token * l, Token * r);
	SemiToken();
	void setLeft(Token * l);
	void setRight(Token * r);
	virtual int execute();
};

#endif
