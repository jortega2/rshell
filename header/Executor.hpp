#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

#include "Token.hpp"
#include <vector>
#include <string>

class Executor {
private:
	std::vector<std::string> args;
	std::vector<Token *> tokens;
	bool valid;
	int ret;
public:
	Executor(std::vector<std::string> args);
	void createTokens();
	bool isValid();
	int execute();
};

#endif
