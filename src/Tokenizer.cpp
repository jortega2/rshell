#include "../header/Tokenizer.hpp"
#include "../header/Token.hpp"
#include "../header/cmdToken.hpp"

Tokenizer::Tokenizer(std::string arg) {
	//regex for connectors but not in quotes
	boost::regex conRegEx("(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	//regex for comments but not in quotes
	boost::regex comRegEx("(#)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	
	if (arg != ""){
		//parse and delete comments, mindful of quotes
		boost::sregex_token_iterator c (arg.begin(), arg.end(), comRegEx, -1);
		//assign arg with new string without comments
		arg = *c;
	}
	
	//end iterator for comparison
	boost::sregex_token_iterator end;

	//temp variables with command
	std::string temp1 = arg;
	std::string temp2 = arg;
			
	//variable for regex seach
	boost::smatch cons;
			
	//parse and find all connectors, put into connector vector
	while (boost::regex_search(temp1, cons, conRegEx)){
                connectors.push_back(cons.str(0));
                temp1 = cons.suffix();
       	}		

	//split commands and arguments from connecotrs
	boost::sregex_token_iterator p(temp2.begin(), temp2.end(), conRegEx, -1);
        	
	//assign commands into vector
        while (p != end){       	
		arguments.push_back(*p++);
       	}
	//check if any arguments are just whitespace (e.g. echo 1 &&     || ls) will get split  into (echo 1,    , ls)
	//if there is, delete that argument to make (echo1, ls)
	//this doesn't fix user input, error will still be detected 
	//this is important in determining if input has correct use of connectors later on
	for (int i = 0; i < arguments.size(); i++){
        	int whitespace = 0;
        	for (int j = 0; j <arguments[i].size(); j++){
            		if (isspace(arguments[i][j])){
                		if (isspace(arguments[i][j])){
                  			whitespace++;
                		}
            		}
        	}
        	if (whitespace == arguments[i].size()){
            		arguments.erase(arguments.begin()+i);
        	}	
    	}
	//if no user input, input empty string for execvp
	if (arguments.empty()){
                arguments.push_back("");
        }
			
}
//get vectors for executor
std::vector<std::string> Tokenizer::returnArgs(){
	return arguments;
}
//get vectors for executor
std::vector<std::string> Tokenizer::returnConns(){
	return connectors;
}
