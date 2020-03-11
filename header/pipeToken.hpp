#ifndef __PIPETOKEN_HPP__
#define __PIPETOKEN_HPP__

#include "Token.hpp"
#include <string>
#include <boost/regex.hpp>

class PipeToken : public Token {
	private:
		std::string dir;
		std::string arg;
		Token* left;
		int ret;
	public:
		PipeToken(std::string input);
		PipeToken(std::string input, Token * l);
		virtual std::string stringify();
		virtual int execute();
		virtual int isLeaf();
		virtual Token* getLeft();
		virtual Token* getRight();
		virtual void setLeft(Token* l);
		virtual void setRight(Token* r);
};

#endif
