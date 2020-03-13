#ifndef __INPUTTOKEN_HPP__
#define __INPUTTOKEN_HPP__

#include "Token.hpp"

class InputToken : public Token {
	private:
		Token* left;
		Token* right;
		int ret;
	public:
		InputToken(Token* l, Token* r);
		InputToken();
		virtual std::string stringify();
		virtual int execute();
		virtual int isLeaf();
		virtual Token* getLeft();
		virtual Token* getRight();
		virtual void setLeft(Token* l);
		virtual void setRight(Token* r);
};

#endif
