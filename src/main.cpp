#include <iostream>
#include "../header/cmdToken.hpp"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

int main() {
	std::string userInput;
	while(1){
		std::cout <<"[rshell]$ ";
		std::getline(std::cin, userInput);
		Tokenizer* command = new Tokenizer(userInput);
		Executor* exec = new Executor(command->returnArgs(), command->returnConns());
		exec->isValid();
		exec->createTokens();
		exec->execute();

	}
	return 0;
}
