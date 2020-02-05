#include <iostream>
#include "../header/Tokenizer.hpp"

int main() {
	std::cout << "Enter \"exit\" to leave shell.\n\n\nEnter a command.\n";
	std::string userInput;
	
	while(1){
		std::cout <<"[rshell] $ ";
		std::getline(std::cin, userInput);
		if (userInput == "exit"){
			break;
		}else{
			Tokenizer* command = new Tokenizer(userInput);
			command->showArguments();
			command->showConnectors();
		}
	}
}
