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
	virtual std::string stringify();
	virtual void setLeft(Token * l);
	virtual void setRight(Token * r);
	virtual Token* getLeft();
	virtual Token* getRight();
	virtual int isLeaf();
	virtual int execute();
};

#endif
