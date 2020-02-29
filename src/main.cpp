#include <iostream>
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

int main() {
	for (int i = 0; i < 3 ; i++){
	std::cout << "[rshell]$ ";
	std::string userInput;
	std::getline(std::cin, userInput);
	Tokenizer* command = new Tokenizer(userInput);
	command->parse();
	command->shuntingYardAlgorithm();
	/*std::vector<std::string> myvec;
	myvec = command->returnArgs();
	for (int i = 0; i < myvec.size(); i++){
		std::cout << myvec[i] << std::endl;
	}*/
	Executor* exec = new Executor(command->returnArgs());
	exec->isValid();
	exec->createTokens();
	exec->execute();
	}
	return 0;
}

/* std::string userInput;
        while(1){
                std::vector<std::string> a;
                std::cout <<"[rshell]$ ";
                std::getline(std::cin, userInput);
                if (userInput == "exit") exit(1);
                Tokenizer* command = new Tokenizer(userInput);
                command->parse();
                command->shuntingYardAlgorithm();
                a = command->returnArgs();
                for (int i = 0; i < a.size(); i++){
                        std::cout << a[i] << std::endl;
                }*/
