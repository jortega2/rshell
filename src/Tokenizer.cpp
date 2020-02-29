#include "../header/Tokenizer.hpp"
#include "../header/Token.hpp"
#include "../header/cmdToken.hpp"
#include <queue>
#include <stack>

Tokenizer::Tokenizer(std::string arg) {
	this->arg = arg;
}

void Tokenizer::parse(){
	//regular expressions for parsing
	boost::regex conRegEx("^\\s*(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
	boost::regex comRegEx("(#)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        boost::regex par1("^\\s*(\\()(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        boost::regex par2("^\\s*(\\))(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        boost::regex argRegEx("(&&|;|\\|\\||\\)|\\()(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        boost::regex leadingSpace("^[ \t]+");
        boost::regex trailingSpace("[ \t]+$");
	
	//temporary variables
	boost::smatch coms;		

	//delete comments
	if (boost::regex_search (arg, coms, comRegEx)){
	        arg = coms.prefix();
        }
	
	//parse function
	do {
                boost::smatch thing;
                if (boost::regex_search(arg, thing, par1)){
                        //std::cout << "parenthesis one found" << std::endl;
                        temp.push_back(thing.str(0));
                        arg = thing.suffix();
                } else if (boost::regex_search(arg, thing, par2)){
                        //std::cout << "parenthesis two found" << std::endl;
                        temp.push_back(thing.str(0));
                        arg = thing.suffix();
                } else if (boost::regex_search(arg, thing, conRegEx)){
                        //std::cout << "connector found" << std::endl;
                        temp.push_back(thing.str(0));
                        arg = thing.suffix();
                } else {
                        if (boost::regex_search(arg, thing, argRegEx)){
                                //std::cout << "before connector" << std::endl;
                                temp.push_back(thing.prefix());
                                arg = arg.substr(thing.position());
                        }
                        else {
                                //std::cout << "no connectors left" << std::endl;
                                temp.push_back(arg);
                                arg = "";
                        }
                }
        } while (arg != "");
	
	//delete empty arguments
	for (int i = 0; i < temp.size(); i++){
        	int whitespace = 0;
        	for (int j = 0; j <temp[i].size(); j++){
            		if (isspace(temp[i][j])){
                  		whitespace++;
            		}
        	}
        	if (whitespace == temp[i].size()){
            		temp.erase(temp.begin()+i);
        	}	
    	}

	//delete leading and trailing white space
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
	//push empty string if userinput was empty
	if (temp.empty()){
                temp.push_back("");
        }
	arguments = temp;	
}

void Tokenizer::shuntingYardAlgorithm(){
	//clear arguments;
	arguments.clear();

	reverse(temp.begin(), temp.end());

	for (int i = 0; i < temp.size(); i++){
                if (temp[i] == "("){
                        temp[i] = ")";
                } else if (temp[i] == ")"){
                        temp[i] = "(";
                }
        }
        /*for (int i = 0; i < temp.size(); i++){
                std::cout << temp[i] << std::endl;
        }*/
	

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
                        myStack.push(temp[i]);
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

        reverse(arguments.begin(), arguments.end());
}
//get vectors for executor
std::vector<std::string> Tokenizer::returnArgs(){
	return arguments;
}
