#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <vector>
#include "Token.hpp"
#include "cmdToken.hpp"

boost::regex conRegEx("(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
boost::regex comRegEx("(#)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");

class Tokenizer {
	private:
		std::vector<std::string> arguments;
		std::vector<std::string> connectors;
		std::vector<Token*> tokens;
	public:
		Tokenizer(std::string arg) {
			//parse and delete comments, mindful of quotes
			boost::sregex_token_iterator c (arg.begin(), arg.end(), comRegEx, -1);
			//end iterator for comparison
			boost::sregex_token_iterator end;
			//assign arg with new string without comments
			arg = *c;
			
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

			//split commands from connecotrs
			boost::sregex_token_iterator p(temp2.begin(), temp2.end(), conRegEx, -1);
        		
			//assign commands into vector
        		while (p != end){
                		
				arguments.push_back(*p++);
        		}	
		}
		void createTokens(){
			/*for (int i = 0; i < arguments.size(); ++i){
				CmdToken * tok = new CmdToken(arguments[i]);
				tok->execute();
				tokens.push_back(tok);
			}*/
		}
		Token * getTokens() {
			return tokens.back();
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
