#ifndef __CMDTOKEN__HPP__
#define __CMDTOKEN__HPP__

#include "Token.hpp"
#include <string>
#include <vector>


class CmdToken : public Token {
	private:
		std::vector<std::string> temp;
		std::vector<char*> args;
	public:
		CmdToken(std::string input);
		virtual void execute();
		std::vector<std::string> returnVector();
};

#endif
