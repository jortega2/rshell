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
		std::vector<std::string> temp;
		std::string arg;
	public:
		Tokenizer(std::string arg);
		void parse();
		void shuntingYardAlgorithm();
		std::vector<std::string> returnArgs();
};
#endif 
