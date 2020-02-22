#ifndef __TESTTOKEN__HPP__
#define __TESTTOKEN__HPP__

#include "Token.hpp"
#include <string>
#include <vector>
#include <boost/regex.hpp>

class TestToken : public Token {
	private:
		std::string file;
		std::string flag;
		int ret;
	public:
		TestToken(std::string input);
		void parse();
		virtual int execute();
		std::string getStrings(std::string which);
		
};
#endif

