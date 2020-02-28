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
	for (int i = 0; i < args.size(); i ++){
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
				i--;
				j++;
			}
		} else {
			i++;
		}			
	}	
}

bool Executor::isValid(){
	//check for valid use of connectors. for 3 connectors there should be 4 arguments to be valid.
	//unless the last connector is ; in which case connectors and arguments can be equal
	/*valid = true;
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
	return valid;*/
}
int Executor::execute(){
//ret represents if execvp called properly or not. If all commands execute properly execute will return 1, 0 otherwise.
	//if (valid == true){
		//ret = tokens.back()->execute();
	//}
	return tokens.front()->execute();
}
