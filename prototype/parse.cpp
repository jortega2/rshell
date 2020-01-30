#include <iostream>
#include <boost/regex.hpp>
#include <string>

using namespace std;

bool parse(string& command){
	//temp
	string temp1 = command;
	string temp2 = command;

	//regexs
        boost::regex executableRegex("(^([\\w]+)|(\\-\\w*[^\\s&|;]))|(?<=[\\|&;]\\s)(\\w+)");
	boost::regex connectorRegEx("&&|;|\\|\\|");

	//smatches
	boost::smatch connectors;
	boost::smatch executables;
	
	vector<string> connectorTokens;
	vector<string> executableTokens;
	
	while (boost::regex_search(temp1, connectors, connectorRegEx)){
		connectorTokens.push_back(connectors.str(0));
		temp1 = connectors.suffix();
	}
	
	while (boost::regex_search(temp2, executables, executableRegex)){
                executableTokens.push_back(executables.str(0));
                temp2 = executables.suffix();
        }
	
	cout << "Found " << connectorTokens.size() << " connectors" << endl;
	cout << "Found " << executableTokens.size() << " executables" << endl;
	//cout << "original command: " <<  command << endl;

        return 1;
}

int main()
{
	string command;
	cout << "\n\nType \"exit\" to leave shell.\n\nDoes not yet detect arguments, only connectors and executables.\n";
	while(1){
		cout << "[rshell ]$ ";
		getline(cin, command);
		if (command == "exit")
			break;
		parse(command);
	}

	return 0;
}

