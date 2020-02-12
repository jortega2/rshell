#include "../header/cmdToken.hpp"
#include <boost/regex.hpp>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

boost::regex cmdRegEx("(?<=\")[^\"]*(?=\")|[^\\s\"]+");

CmdToken::CmdToken(std::string input) { 
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
int CmdToken::execute() {
	int status;
	char ** command =  &args[0];
	pid_t split  = fork();
	if (split == -1){
		perror("fork failed, check processes");
		exit(1);
	}
	if (split == 0)	{
		//std::cout << "child: " << split << std::endl;
		if (execvp(command[0], command) == -1){
			perror(args[0]);
		}
		exit(1);
	}
	if (split > 0){
		waitpid(split, &status, WUNTRACED);
		if ((WIFEXITED(status))){
			if (WEXITSTATUS(status) == 1){
				ret = 0;
			}
		}
	}
	return ret;
}
std::vector<std::string> CmdToken::returnVector(){
	return temp;
}
