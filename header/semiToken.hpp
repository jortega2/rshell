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
	virtual void setLeft(Token * l);
	virtual void setRight(Token * r);
	virtual Token* getLeft();
	virtual Token* getRight();
	virtual int isLeaf();
	virtual int execute();
};

#endif
