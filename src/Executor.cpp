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
	//create the tree of commands, but only if connector usage is valid
	if (valid == true){
		for (int i = 0; i <arguments.size(); i++){
			CmdToken * tok = new CmdToken(arguments[i]);
			tokens.push_back(tok);
		}
		for (int i = 0; i < connectors.size(); i++){
                	if (((i+1) == connectors.size()) && (connectors.back() == ";")){
                        	if ((arguments.size() - connectors.size()) == 1){
                                        Token * tok =  new SemiToken(tokens.back(), tokens[i+1]);
					tokens.push_back(tok);
				}
                        	else if ((arguments.size() - connectors.size()) == 0){
                                        Token * tok = new SemiToken(tokens.back());
					tokens.push_back(tok);
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
}

bool Executor::isValid(){
	//check for valid use of connectors. for 3 connectors there should be 4 arguments to be valid.
	//unless the last connector is ; in which case connectors and arguments can be equal
	valid = true;
	if (connectors.empty()){
		
	}else if ((connectors.back() == "&&") || (connectors.back() ==  "||")){
		if (connectors.size() >= arguments.size()){
			std::cout << "Invalid use of connectors\n";
			valid = false;
		}
	} else if (connectors.back() == ";"){
		if (connectors.size() > arguments.size()){
			std::cout << "Invalid use of connectors\n";
			valid = false;
		}
	} 
	return valid;
}
int Executor::execute(){
//ret represents if execvp called properly or not. If all commands execute properly execute will return 1, 0 otherwise.
int ret = 0;
	if (valid == true){
		ret = tokens.back()->execute();
	}
	return ret;
}
