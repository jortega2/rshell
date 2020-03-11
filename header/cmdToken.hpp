#ifndef __CMDTOKEN__HPP__
#define __CMDTOKEN__HPP__

#include "Token.hpp"
#include <string>
#include <vector>
#include <boost/regex.hpp>

class CmdToken : public Token {
	private:
		std::vector<std::string> temp;
		std::vector<char*> args;
		std::string arg;
		int ret;
	public:
		CmdToken(std::string input);
		virtual std::string stringify();
		virtual int execute();
		virtual int isLeaf();
		virtual Token* getLeft();
		virtual Token* getRight();
		virtual void setLeft(Token* l){};
		virtual void setRight(Token * r){};
		std::vector<std::string> returnVector();
};

#endif
