#include <iostream>
#include "../header/cmdToken.hpp"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"
#include "../header/testToken.hpp"

int main() {
	/*for (int i = 0; i < 2 ; i++){
	std::cout << "[rshell]$ ";
	std::string userInput;
	std::getline(std::cin, userInput);
	TestToken* test = new TestToken(userInput);
	test->execute();
	}*/
	std::string userInput;
	while(1){
		std::vector<std::string> a;
		std::cout <<"[rshell]$ ";
		std::getline(std::cin, userInput);
		if (userInput == "exit") exit(1);
		Tokenizer* command = new Tokenizer(userInput);
		a = command->returnArgs();
		for (int i = 0; i < a.size(); i++){
			std::cout << a[i] << std::endl;
		}
		/*Executor* exec = new Executor(command->returnArgs(), command->returnConns());
		exec->isValid();
		exec->createTokens();
		exec->execute();*/

	}
	return 0;
}
