#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

#include "Token.hpp"
#include <vector>
#include <string>

class Executor {
private:
	std::vector<std::string> arguments;
	std::vector<std::string> connectors;
	std::vector<Token *> tokens;
public:
	Executor(std::vector<std::string> args, std::vector<std::string> conns);
	void createTokens();
	bool isValid();
	int execute();
};

#endif
