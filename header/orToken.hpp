#ifndef __ORTOKEN_HPP__
#define __ORTOKEN_HPP__

#include "Token.hpp"

class OrToken : public Token{
private:
	Token * left;
	Token * right;
	int ret;
public:
	OrToken(Token * l, Token * r);
	virtual int execute();
};

#endif
