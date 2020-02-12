#include <iostream>
#include "../header/cmdToken.hpp"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

int main() {
	
	std::cout << "Enter \"exit\" to leave shell.\n\n\nEnter a command.\n";
	std::string userInput;
	
	for (int i = 0; i < 5; i++) {
		std::cout <<"[rshell] $ ";
		std::getline(std::cin, userInput);
		if (userInput == "exit"){
			i+=10;
		}else{
			Tokenizer* command = new Tokenizer(userInput);
			//command->showArguments();
			//command->showConnectors();
			Executor* exec = new Executor(command->returnArgs(), command->returnConns());
			exec->createTokens();
			exec->execute();
		}
	}
	return 0;
}
