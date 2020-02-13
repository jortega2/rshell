#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"
#include "../header/orToken.hpp"
#include "../header/semiToken.hpp"

Executor::Executor(std::vector<std::string> args, std::vector<std::string> conns) {
	arguments = args;
	connectors = conns;
}

void Executor::createTokens() {
	for (int i = 0; i <arguments.size(); i++){
		CmdToken * tok = new CmdToken(arguments[i]);
		tokens.push_back(tok);
	}
	for (int i = 0; i < connectors.size(); i++){
                if (((i+1) == connectors.size() &&  arguments.back() == ";")){
                        if ((arguments.size() - connectors.size()) == 1){
                                if (connectors.back() == ";"){
                                        Token * tok =  new SemiToken(tokens.back(), tokens[i+1]);
					tokens.push_back(tok);
                                }
			}
                        else if ((arguments.size() - connectors.size()) == 0){
                                if (connectors.back() == ";"){
                                        Token * tok = new SemiToken(tokens.back());
					tokens.push_back(tok);
                                }
                        }	
		}else if (i == 0){
                    if (connectors[i] == "&&"){
                        Token * tok = new AndToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }else if (connectors[i] == "||"){
                        Token * tok = new OrToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }else if (connectors[i] == ";"){
                        Token * tok = new SemiToken(tokens[i], tokens[i+1]);
                        tokens.push_back(tok);
                    }
		 
		}else {
                        if (connectors[i] == "&&"){
                            Token * tok = new AndToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        } else if (connectors[i] == "||"){
                            Token * tok = new OrToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        } else if (connectors[i] == ";"){
                            Token * tok = new SemiToken(tokens.back(), tokens.at(i+1));
                            tokens.push_back(tok);
                        }
                }
       }
}

bool Executor::isValid(){
	int ret = 1;
	if (connectors.empty()){
		
	}else if ((connectors.back() == "&&") || (connectors.back() ==  "||")){
		if (connectors.size() >= arguments.size()){
			std::cout << "Invalid use of connectors\n";
			ret = 0;
		}
	} else if (connectors.back() == ";"){
		if (connectors.size() > arguments.size()){
			std::cout << "Invalid use of connectors\n";
			ret = 0;
		}
	} 
	return ret;
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
