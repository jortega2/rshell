#include "../header/pipeToken.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <fcntl.h>
#include <vector>
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
	std::string r = "r";
	std::string w = "w";
	char buffer[PATH_MAX];
	memset(buffer, '\0', 420);
	
	FILE* in_pipe = popen(left->stringify().c_str(), r.c_str());
	FILE* out_pipe = popen(dir.c_str(), w.c_str());
	
	if ((in_pipe != nullptr) && (in_pipe != nullptr)){
		while (fgets(buffer,PATH_MAX, in_pipe) != nullptr){
			fputs(buffer, out_pipe);
		}
		ret = 1;
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
	
	return ret;
}
