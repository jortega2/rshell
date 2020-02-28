#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__
#include <iostream>

class Token {
	public:
		virtual int execute() = 0;
		virtual int isLeaf() = 0;
		virtual Token* getLeft() = 0;
		virtual Token* getRight() = 0;
		virtual void setLeft(Token* l) = 0;
		virtual void setRight(Token* r) = 0;
};
#endif
