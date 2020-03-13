#include "../header/cmdToken.hpp"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

CmdToken::CmdToken(std::string input) { 
	arg = input;
	boost::regex cmdRegEx("(?<=\")[^\"]*(?=\")|[^\\s\"]+");
	ret = 1;
	boost::smatch tempargs;
	while(boost::regex_search(input, tempargs, cmdRegEx)){
		temp.push_back(tempargs.str(0));
		input = tempargs.suffix();
	}	
	
	for (int i = 0; i < temp.size(); i++){
		args.push_back((char*)temp[i].c_str());
	}
	args.push_back(NULL);
			
}

int CmdToken::isLeaf() {
	return 1;
}

std::string CmdToken::stringify(){
	boost::smatch ws1, ws2;

	boost::regex leadingSpace("^[ \t]+");
        boost::regex trailingSpace("[ \t]+$");
	if (boost::regex_search(arg, ws1, leadingSpace)){
                arg = ws1.suffix();
        }
        if (boost::regex_search(arg, ws2, trailingSpace)){
                arg = ws2.prefix();
        }
        return arg;
}


Token* CmdToken::getLeft(){
        return nullptr;
}

Token* CmdToken::getRight(){
        return nullptr;
}

int CmdToken::execute() {
	//if execvp throws in error, ret will be assigned 0. otherwise it will be 1.
	//this is used for connector logic, as well as unit tests.
	int status ;
	char ** command =  &args[0];
	
	if (!(temp.empty())){
		if (temp[0]  == "exit") {
			exit(1);
		}
	}
	pid_t split  = fork();
	if (split == -1){
		perror("fork failed, check processes");
		exit(1);
	}
	if (split == 0)	{
		execvp(command[0], command);
		perror(args[0]);
		exit(1);
	}
	if (split > 0){
		waitpid(split, &status, WUNTRACED);
		if ((WIFEXITED(status))){
			if ( WEXITSTATUS(status) != 0){
				ret = 0;
			}
		}
	}
	return ret;
}
//used only for unit tests
std::vector<std::string> CmdToken::returnVector(){
	return temp;
}
