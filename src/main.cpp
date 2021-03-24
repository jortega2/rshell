#include <iostream>
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

int main() {
	while(1){
		std::cout << "[rshell]$ ";

		std::string userInput;
		std::getline(std::cin, userInput);

		Tokenizer* command = new Tokenizer(userInput);
		command->parse();
		
		command->shuntingYardAlgorithm();
		Executor* exec = new Executor(command->returnArgs());
		exec->isValid();
		exec->createTokens();
		exec->execute();
	}
	return 0;
}

