#include "../header/testToken.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



TestToken::TestToken(std::string input){
	file = input;
	this->parse();
}

void TestToken::parse(){
	boost::regex firstWord("^\\s*([\\w]+)");
	boost::regex openBracket("(\\[)");
	boost::regex closeBracket("(\\])");
	boost::regex getFlag("^\\s*-(\\w)+");
	boost::regex leadingSpace("^[ \t]+");
	boost::regex trailingSpace("[ \t]+$");
	
	//parse command into flag and command strings, methods vary depending on format
	boost::smatch word, openB, closedB, fl, ws1, ws2;
	flag = "";
	if (boost::regex_search(file, word, firstWord)){
		file = word.suffix();
	}
	else if(boost::regex_search(file, openB, openBracket)){
		file = openB.suffix();
			if (boost::regex_search(file, closedB, closeBracket)){
                		file = closedB.prefix();
        	}
	}
	
	if (boost::regex_search(file, fl, getFlag)){
		flag = fl.str(0);
		file = fl.suffix();
        }
	//delete leading/trailing whitespace
	if (boost::regex_search(file, ws1, leadingSpace)){
		file = ws1.suffix();
	}
	if (boost::regex_search(flag, ws1, leadingSpace)){
                flag = ws1.suffix();
        }
	if (boost::regex_search(file, ws2, trailingSpace)){
		file = ws2.prefix();
	}
	if (boost::regex_search(flag, ws2, trailingSpace)){
                flag = ws2.prefix();
        }
}

int TestToken::isLeaf(){
	return 1;
}

Token* TestToken::getLeft(){
        return nullptr;
}

Token* TestToken::getRight(){
        return nullptr;
}

int TestToken::execute(){
	struct stat cmd;
	char* myCmd = (char*)file.c_str();

	if (stat(myCmd, &cmd)>=0){
		if (flag == "-f"){
			if ((S_ISREG(cmd.st_mode) != 0)){
				std::cout << "(true)\n";
				ret = 1;
			} else {
				std::cout << "(false)\n";
				ret = 0;
			}
		} else if (flag == "-d"){
                	if ((S_ISDIR(cmd.st_mode) != 0)){
                        	std::cout << "(true)\n";
				ret = 1;
                	} else {
                        	std::cout << "(false)\n";
				ret = 0;
                	}
		} else if (flag == "-e" || flag == ""){
			if ((S_ISREG(cmd.st_mode) != 0)){
				std::cout << "(true)\n";
				ret = 1;
			} else if ((S_ISDIR(cmd.st_mode) != 0)){
				std::cout << "(true)\n";
				ret = 1;	
			} else {
				std:: cout << "(false)\n";
				ret = 0;
			}
		} else {
			std::cout << "invalid flag\n";
			ret = 0;
		}	
	} else { 
		std::cout << "(false)\n";
		ret = 0;
	}
	
	return ret;
}

std::string TestToken::getStrings(std::string which){
	std::string rets;
	
	if (which == "flag"){
		rets = flag;
	} else if (which == "file"){
		rets = file;
	}
	return rets;
}
	

