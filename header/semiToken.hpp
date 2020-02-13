#ifndef __SEMITOKEN_HPP__
#define __SEMITOKEN_HPP__

#include "Token.hpp"

class SemiToken : public Token {
private:
	Token * left;
	Token * right;
	int ret;
public:
	SemiToken(Token * l);
	SemiToken(Token * l, Token * r);
	virtual int execute();
};

#endif
