#include "../header/inputToken.hpp"
//#include <thread>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// tr a-z A-Z <  path/to/dir
InputToken::InputToken(Token* l, Token* r){
	left = l;
	right = r;
	//parse
	/*boost::regex argRegEx("(\\<)|\\()(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex pip("(\\<)");
	boost::smatch symbol;
	if (boost::regex_search(input, symbol, pip)){
		input = symbol.suffix();
	}*/
}

InputToken::InputToken(){
	left = nullptr;
	right = nullptr;
}	

int InputToken::isLeaf(){
	return 0;
}

void InputToken::setLeft(Token* l){
	left = l;
}

void InputToken::setRight(Token* r){
	right = r;
}

Token* InputToken::getLeft(){
	return left;
}

Token* InputToken::getRight(){
	return right;
}

std::string InputToken::stringify(){
        return left->stringify() + " < " + right->stringify();
}


int InputToken::execute(){	
	ret = 0;
	int status, op;
	pid_t split = fork();

	if (split == -1){
		perror("fork failed, echck processes");
	}
	if (split == 0){ 
		std::string r = "r";
		std::string w = "w";
		
		int PATH_MAX = 420;
		char buffer[PATH_MAX];
		memset(buffer, '\0', 420);

		op = open(right->stringify().c_str(), O_RDONLY);
		FILE* out_pipe = popen(left->stringify().c_str(), w.c_str());
		
		if (op == -1){
			perror(right->stringify().c_str());
			ret = 0;
		}
	
		else if (read(op, buffer, PATH_MAX) == -1){
			ret = 0;
		}
		else if (out_pipe == NULL || out_pipe == nullptr){
			ret = 0;
		}
		if (fputs(buffer, out_pipe) != -1){
			ret = 1;
		}
		
		close(op);
		pclose(out_pipe);
		std::cout << "ret ret \n\n";
		exit(ret);
	}
	if (split > 0){
		waitpid(split, &status, WUNTRACED);
			if((WIFEXITED(status))){
				if (WEXITSTATUS(status) == 1){
					ret = 1;
				} else {
					ret = 0;
				}
			}
	}
	return ret;
}
