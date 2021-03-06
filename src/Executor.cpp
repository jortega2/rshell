#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"
#include "../header/orToken.hpp"
#include "../header/semiToken.hpp"
#include "../header/testToken.hpp"

Executor::Executor(std::vector<std::string> args) {
	this->args = args;
}

void Executor::createTokens() {
	if (valid == true) {
		std::vector<int> prev;
		//get positions of connectors for indexing
		for (int i = 0; i < args.size(); i++){
			if (args[i] == "&&" || args[i] == ";" || args[i] == "||"){
				prev.push_back(i);
			}
		}
		//create tokens
		for (int i = 0; i < args.size(); i++){
			if (args[i] == "&&"){
				AndToken * tok = new AndToken();
				tokens.push_back(tok);
			} else if (args[i] == "||"){
				OrToken * tok = new OrToken();
				tokens.push_back(tok);
			} else if (args[i] == ";"){
				SemiToken * tok = new SemiToken();
				tokens.push_back(tok);
			} else if ((args[i][0] == '[' && args[i][args[i].size()-1] == ']' && args[i][1] == ' ' && args[i][args[i].size()-2] == ' ') || (args[i][0] == 't' && args[i][1] == 'e' && args[i][2] == 's' && args[i][3] == 't')) {
				TestToken * tok = new TestToken(args[i]);
				tokens.push_back(tok);
			} else {
				CmdToken * tok = new CmdToken(args[i]);
				tokens.push_back(tok);
			}
		}
		//make tree
		int i = 0;
		for ( int j = 1; j < tokens.size();){
			if (tokens[i]->isLeaf() == 1) {
				i++;
			} else if (tokens[i]->getLeft() == nullptr){
				tokens[i]->setLeft(tokens[j]);	
				if (tokens[j]->isLeaf() == 0){
					i++;
					j++;
				} else if (tokens[j]->isLeaf() == 1){
					j++;
				}
			} else if (tokens[i]->getRight() == nullptr){
				tokens[i]->setRight(tokens[j]);
				if (tokens[j]->isLeaf() == 0){
					i++;
					j++;
				} else if (tokens[j]->isLeaf() == 1) {
					j++;
					//go back to lowest unfinshed composite
					for (int k = prev.size() - 1; k >= 0; k--){
						if (prev[k] < i){
							if (tokens[prev[k]]->getLeft() == nullptr || tokens[prev[k]]->getRight() == nullptr){
								i = prev[k];
								break;
							}
						}
					}
				}
			} else {
				if (i < tokens.size() - 1){
					i++;
				} else {
					std::cout << "failed gracefully...\n";
					break;
				}
			}			
		}
	}	
}

bool Executor::isValid(){
	//check for valid use of connectors. for 3 connectors there should be 4 arguments to be valid.
	//unless the last connector is ; in which case connectors and arguments can be equal
	valid = true;
	int cons = 0;
	if (!(args.empty())){
		for (int i = 0; i < args.size(); i++) {
			if (args[i] == "&&" || args[i] == ";" || args[i] == "||"){
				cons++;
			}
		}
		if (cons + 1 !=  (args.size() - cons)){
			std::cout << "invalid use of connectors\n";
			valid = false;
		}
	}
				
	return valid;
}
int Executor::execute(){
//ret represents if execvp called properly or not. If all commands execute properly execute will return 1, 0 otherwise.
	ret = 0;
	if (valid == true){
		ret = tokens.front()->execute();
	}
	return ret;
}
