#ifndef __TESTTOKEN__HPP__
#define __TESTTOKEN__HPP__

#include "Token.hpp"
#include <string>
#include <vector>
#include <boost/regex.hpp>

class TestToken : public Token {
	private:
		std::string arg;
		std::string file;
		std::string flag;
		int ret;
	public:
		TestToken(std::string input);
		virtual std::string stringify();
		void parse();
		virtual int execute();
		virtual int isLeaf();
		virtual Token* getRight();
		virtual Token* getLeft();
		virtual void setRight(Token* l){};
		virtual void setLeft(Token* r){};
		std::string getStrings(std::string which);
		
};
#endif

