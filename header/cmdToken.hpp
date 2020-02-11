#ifndef __CMDTOKEN__HPP__
#define __CMDTOKEN__HPP__

#include "Token.hpp"
#include <boost/regex.hpp>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <stdio.h>

boost::regex cmdRegEx("(?<=\")[^\"]*(?=\")|[^\\s\"]+");

class CmdToken : public Token {
	private:
		std::vector<std::string> temp;
		std::vector<char*> args;
	public:
		CmdToken(std::string input) { 
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
		virtual void execute() {
			int status;
			char ** command =  &args[0];

			pid_t split  = fork();
			if (split == -1){
				perror("command failed");
				exit(1);
			}
			if (split == 0)
			{
				std::cout << "child: " << split << std::endl;
				execvp(command[0], command);
				exit(1);
			}
			if (split > 0){
				waitpid(split, &status, WUNTRACED);
			}
		}
		std::vector<std::string> returnVector(){
			return temp;
		}
};

#endif
