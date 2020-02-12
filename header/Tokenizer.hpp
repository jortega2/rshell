#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "Token.hpp"
#include <iostream>
#include <vector>
#include <string>

class Tokenizer {
	private:
		std::vector<std::string> arguments;
		std::vector<std::string> connectors;
		std::vector<Token*> tokens;
	public:
		Tokenizer(std::string arg);
		void createTokens();
		Token * getTokens();
		std::vector<std::string> returnArgs();
		void showArguments();
		void showConnectors();
};
#endif 
