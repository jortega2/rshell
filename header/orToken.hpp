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
	OrToken();
	virtual std::string stringify();
	virtual void setLeft(Token * l);
	virtual void setRight(Token * r);
	virtual Token* getLeft();
	virtual Token* getRight();
	virtual int isLeaf();
	virtual int execute();
};

#endif
