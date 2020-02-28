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
	//boost::regex whiteSpace("[^\\s]+");
	//delete first word, should only ever be test because of tokenizer
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
	/*if (flag != ""){
                std::cout << "flag: " << flag << std::endl;
        }

        std::cout << "file: " << file << std::endl;*/

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
	/*if (flag != ""){
		std::cout << "flag: " <<  flag << std::endl;
	}
	
	std::cout << "file: " <<  file << std::endl;*/
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
	
	stat(myCmd, &cmd);

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
		std::cout << "something went terribly wrong...\n";
		ret = 2;
	}
	
	
	
	return ret;
}

std::string TestToken::getStrings(std::string which){
	std::string ret;
	
	if (which == "flag"){
		ret = flag;
	} else if (which == "file"){
		ret = file;
	}
	return ret;
}
	

