#include "../header/Tokenizer.hpp"
#include "../header/Token.hpp"
#include "../header/cmdToken.hpp"
#include <queue>
#include <stack>

Tokenizer::Tokenizer(std::string arg) {
	//regex for connectors but not in quotes
	boost::regex conRegEx("^\\s*(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	//regex for comments but not in quotes
	boost::regex comRegEx("(#)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex par1("^\\s*(\\()(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex par2("^\\s*(\\))(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex argRegEx("(&&|;|\\|\\||\\)|\\()(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex leadingSpace("^[ \t]+");
	boost::regex trailingSpace("[ \t]+$");
	//boost::regex argRegEx(".+?(?=&&|\\|\\||;|\\(|\\)|$)");
	boost::smatch coms;
	
	//temp string vector
	std::vector<std::string> temp;
	
	//parse and delete comments, mindful of quotes
	if (boost::regex_search (arg, coms, comRegEx)){
	//assign arg with new string without comments
		arg = coms.prefix();
	}

	do {
		boost::smatch thing;
		if (boost::regex_search(arg, thing, par1)){
			std::cout << "parenthesis one found" << std::endl;
			temp.push_back(thing.str(0));
			arg = thing.suffix();
		} else if (boost::regex_search(arg, thing, par2)){
			std::cout << "parenthesis two found" << std::endl;
			temp.push_back(thing.str(0));
			arg = thing.suffix();
		} else if (boost::regex_search(arg, thing, conRegEx)){
			std::cout << "connector found" << std::endl;
			temp.push_back(thing.str(0));
			arg = thing.suffix();
		} else {
			if (boost::regex_search(arg, thing, argRegEx)){
				std::cout << "before connector" << std::endl;
				temp.push_back(thing.prefix());
				arg = arg.substr(thing.position());
			}
			else {
				std::cout << "no connectors left" << std::endl;
				temp.push_back(arg);
				arg = "";
			}
		}
	} while (arg != "");
	

	//delete leading/trailing white space
	for (int i = 0; i < temp.size(); i++){
		boost::smatch ws;
		if (boost::regex_search(temp[i], ws, leadingSpace)){
			temp[i] = ws.suffix();
		}
	}

	for (int i = 0; i < temp.size(); i++){
                boost::smatch ws;
                if (boost::regex_search(temp[i], ws, trailingSpace)){
                       temp[i] = ws.prefix();
                }
        }
	//mirror vector
	reverse(temp.begin(), temp.end());
	//invert parenthesis
	for (int i = 0; i < temp.size(); i++){
		if (temp[i] == "("){
			temp[i] = ")";
		} else if (temp[i] == ")"){
			temp[i] == "(";
		}
	}
	for (int i = 0; i < temp.size(); i++){
		std::cout << temp[i] << std::endl;
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	//shuting yard algorithm
	std::stack<std::string> myStack;
	std::queue<std::string> myQueue;
	
	for (int i = 0; i < temp.size(); i++){
		if (temp[i] == "("){
			myStack.push(temp[i]);
		} else if (temp[i] == ")") {
			while (!(myStack.empty()) && (myStack.top() != "(")){
				myQueue.push(myStack.top());
				myStack.pop();
			}
			if (!(myStack.empty()) && myStack.top() == "(") {
				myStack.pop();
			}
		} else if ((temp[i] == "||") || (temp[i] == "&&") || (temp[i] == ";")){
			if (!(myStack.empty()) && myStack.top() != "("){
				myQueue.push(temp[i]);
				while (!(myStack.empty()) && (myStack.top() != "(")){
                                	myQueue.push(myStack.top());
                                	myStack.pop();
                        	} 
			} else {	
				myStack.push(temp[i]);
			}
		} else {
			myQueue.push(temp[i]);
		}
	}
	
	while (!(myStack.empty())){
		myQueue.push(myStack.top());
		myStack.pop();
	}

	for (int i = myQueue.size()-1; i >= 0; i--){
		arguments.push_back(myQueue.front());
		myQueue.pop();
	}
		
	//end iterator for comparison
	//boost::sregex_token_iterator end;

	//temp variables with command
	//std::string temp1 = arg;
	//std::string temp2 = arg;
	
			
	//variable for regex seach
	//boost::smatch cons;
			
	//parse and find all connectors, put into connector vector
	/*while (boost::regex_search(temp1, cons, conRegEx)){
                connectors.push_back(cons.str(0));
                temp1 = cons.suffix();
       	}		

	//split commands and arguments from connecotrs
	boost::sregex_token_iterator p(temp2.begin(), temp2.end(), conRegEx, -1);
        	
	//assign commands into vector
        while (p != end){       	
		arguments.push_back(*p++);
       	}*/
	//check if any arguments are just whitespace (e.g. echo 1 &&     || ls) will get split  into (echo 1,    , ls)
	//if there is, delete that argument to make (echo1, ls)
	//this doesn't fix user input, error will still be detected 
	//this is important in determining if input has correct use of connectors later on
	/*for (int i = 0; i < arguments.size(); i++){
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
    	}*/
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
