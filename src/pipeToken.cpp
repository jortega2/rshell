#include "../header/pipeToken.hpp"
//#include <thread>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>


PipeToken::PipeToken(std::string input){
	arg = input;
	//parse
	boost::regex pip("(\\|)");
	boost::smatch symbol;
	if (boost::regex_search(input, symbol, pip)){
		input = symbol.suffix();
	}
	dir = input;
}

PipeToken::PipeToken(std::string input, Token * l){
	arg = input;
	left = l;
	//parse
	boost::regex pip("(\\|)");
        boost::smatch symbol;
        if (boost::regex_search(input, symbol, pip)){
                input = symbol.suffix();
        }
	dir = input;
}

int PipeToken::isLeaf(){
	return 0;
}

void PipeToken::setLeft(Token* l){
	left = l;
}

void PipeToken::setRight(Token* r){}

Token* PipeToken::getLeft(){
	return left;
}

Token* PipeToken::getRight(){
	return nullptr;
}

std::string PipeToken::stringify(){
        return left->stringify() + " " + arg;
}


int PipeToken::execute(){	
	ret = 0;
	int status;
	pid_t split = fork();

	if (split == -1){
		perror("fork failed, echck processes");
	}
	if (split == 0){ 
		std::string r = "r";
		std::string w = "w";

		char buffer[PATH_MAX];
		memset(buffer, '\0', 420);

		FILE* in_pipe = popen(left->stringify().c_str(), r.c_str());
		FILE* out_pipe  = popen(dir.c_str(), w.c_str()); 

		if ((in_pipe != NULL) && (out_pipe != NULL)){
			while (fgets(buffer,PATH_MAX, in_pipe) != NULL){
				//std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				fputs(buffer, out_pipe);
			}
			ret = 1;
			//std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		} else {
			if (in_pipe == nullptr){
				perror("in_pipe");
			}
			if (out_pipe == nullptr){
				perror("out_pipe");
			}
			ret = 0;
		}
		
		pclose(in_pipe);
		pclose(out_pipe);
		exit(1);
	}
	if (split > 0){
		waitpid(split, &status, WUNTRACED);
			if((WIFEXITED(status))){
				if (WEXITSTATUS(status) != 0){
					ret = 1;
				}
			}
	}
	return ret;
}
