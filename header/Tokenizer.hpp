#ifndef __TOKENIZER_HPP__
#define __BASE_HPP__
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <algorithm>
#include <vector>
#include <boost/xpressive/xpressive.hpp>

//boost::regex cmdRegex("([^&|;][^&|;]+(\".+\"\\s*))|([^&|;][^&|;]+?(?=&&|\\|\\||;|$))");
boost::regex conRegEx("(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
boost::regex comRegEx("(#)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");

class Tokenizer {
	private:
		std::vector<std::string> arguments;
		std::vector<std::string> connectors;
	public:
		Tokenizer(std::string arg) {
			//temp variables with command
			std::string temp1 = arg;
			std::string temp2 = arg;
			
			//variable for regex seach
			boost::smatch cons;
			
			//parse and find all variables, put into connector vector
			while (boost::regex_search(temp1, cons, conRegEx)){
                		connectors.push_back(cons.str(0));
                		temp1 = cons.suffix();
        		}		
			//parse and delete comments, mindful of quotes
			boost::sregex_token_iterator c(temp2.begin(), temp2.end(), comRegEx, -1);
			//end iterator for comparison of other iterators
			boost::sregex_token_iterator end;
			
			//assign temp2 with argument but comments are now deleted
			temp2 = *c;

			//split commands from connecotrs
			boost::sregex_token_iterator p(temp2.begin(), temp2.end(), conRegEx, -1);
        		
			//assign commands into vector
        		while (p != end){
                		
				arguments.push_back(*p++);
        		}	
			/*while (boost::regex_search(temp2, coms, cmdRegex)){
                                  arguments.push_back(coms.str(0));
                                  temp2 = coms.suffix();
                        }*/
			//delete temp1, temp2, cons, coms;
		}
		std::vector<std::string> returnArgs(){
			return arguments;
		}
		void showArguments() {
			for (int i = 0; i < arguments.size(); i++){
				std::cout << i + 1 << ". " << arguments[i] << std::endl;
			}
		}
		void showConnectors(){
			for ( int i = 0; i < connectors.size(); i++){
                                std::cout << i + 1 << ". " << connectors[i] << std::endl;
                        }
		}
};
#endif 
