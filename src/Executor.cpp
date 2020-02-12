#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"

Executor::Executor(std::vector<std::string> args, std::vector<std::string> conns) {
	arguments = args;
	connectors = conns;
}

void Executor::createTokens() {
	for (int i = 0; i <arguments.size(); ++i){
		CmdToken * tok = new CmdToken(arguments[i]);
		tokens.push_back(tok);
	}
}

void Executor::execute(){
	tokens.back()->execute();
	/*for (int i =0; i < arguments.size(); i++){
		std::cout << arguments[i] << std::endl;
	}
	for (int i =0; i < connectors.size(); i++){
                  std::cout << connectors[i] << std::endl;
          }*/
}
