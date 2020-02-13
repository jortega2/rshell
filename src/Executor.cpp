#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"

Executor::Executor(std::vector<std::string> args, std::vector<std::string> conns) {
	arguments = args;
	connectors = conns;
}

void Executor::createTokens() {
	for (int i = 0; i <arguments.size(); ++i){
		CmdToken * tok = new CmdToken(arguments[i]);
		tokens.push_back(tok);
	}
	for (int i = 0; i < connectors.size(); i++){
                if (i == 0){
                    if (connectors[i] == "&&"){
                        Token * tok = new AndToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }/* else if (connectors[i] == "||"){
                        Token * tok = new OrToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }else if (connectors[i] == ";"){
                        Token * tok = new SemiToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }*/
                } else {
                        if (connectors[i] == "&&"){
                            Token * tok = new AndToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        }/* else if (connectors[i] == "||"){
                            Token * tok = new OrToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        } else if (connectors[i] == ";"){
                            Token * tok = new SemiToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        }*/
                }
       }
}

bool Executor::isValid(){
	if (connectors.size() >= arguments.size()){
		std::cout << "Invalid use of connectors\n";
	}
	return !(connectors.size() >= arguments.size());
}

int Executor::execute(){
	tokens.back()->execute();
	/*for (int i =0; i < arguments.size(); i++){
		std::cout << arguments[i] << std::endl;
	}
	for (int i =0; i < connectors.size(); i++){
                  std::cout << connectors[i] << std::endl;
        }*/
	return 0;
}
