#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "Token.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <boost/regex.hpp>

class Tokenizer {
	private:
		std::vector<std::string> arguments;
		std::vector<std::string> connectors;
	public:
		Tokenizer(std::string arg);
		void createTokens();
		std::vector<std::string> returnArgs();
		std::vector<std::string> returnConns();
};
#endif 
