#ifndef __ANDTOKEN_HPP__
#define __ANDTOKEN_HPP__

#include "Token.hpp"

class AndToken : public Token{
private:
	Token * left;
	Token * right;
	int ret;
public:
	AndToken(Token * l, Token * r);
	AndToken();
	void setLeft(Token * l);
	void setRight(Token * r);
	virtual int execute();
};

#endif
