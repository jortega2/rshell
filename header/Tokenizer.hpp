#ifndef __TOKENIZER_HPP__
#define __BASE_HPP__
#include <iostream>
#include <string>
#include <boost/regex.hpp>

boost::regex cmdRegex("([^&|;][^&|;]+(\".+\"\\s*))|([^&|;][^&|;]+?(?=&&|\\|\\||;|$))");
boost::regex conRegEx("(&&|;|\\|\\|)(?=([^\"]*\"[^\"]*\")*[^\"]*$)");

class Tokenizer {
	private:
		std::vector<std::string> arguments;
		std::vector<std::string> connectors;
		//boost::regex cmdRegex("([^&\\|;][^&\\|;].+?(?=&&))|([^&\\|;][^&\\|;].+?(?=\\|\\|))|([^&\\|;][^&\\|;].+?(?=;))|([^&\\|;][^&\\|;].+?(?=$))");
        	//boost::regex conRegEx("&&|;|\\|\\|");
	public:
		Tokenizer(std::string arg) {
			std::string temp1 = arg;
			std::string temp2 = arg;
			
			boost::smatch cons;
			boost::smatch coms;

			while (boost::regex_search(temp1, cons, conRegEx)){
                		connectors.push_back(cons.str(0));
                		temp1 = cons.suffix();
        		}		

        		while (boost::regex_search(temp2, coms, cmdRegex)){
                		arguments.push_back(coms.str(0));
                		temp2 = coms.suffix();
        		}
		
			//delete temp1, temp2, cons, coms;
		}
		void showStrings(){
			for ( int i = 0; i < arguments.size(); i ++){
				std::cout << i + 1 << ". " << arguments[i] << std::endl;
			}
			for ( int i = 0; i < connectors.size(); i ++){
                                std::cout << i + 1 << ". " << connectors[i] << std::endl;
                        }
		}
};
#endif 
