#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

using namespace std;

void execute(char *args[]) {
	int status;

	pid_t split =  fork();

        if (split == -1){
                cout << "error\n";
        } 
	if (split == 0) {
		//cout << "in child\n";
                execvp(args[0], args);
	}
	if (split > 1) {
		 waitpid(split, &status, WUNTRACED);
		//cout << "parent finished waiting\n";
	}	
	
}

int main(){
	
	cout << "\n\nEnter \"exit\" to leave shell.\n"
		<< "\n\nEnter a simple command. Shell does not support arguments or connectors. Just use ls\n";

	string userInput;
	char *args[2];

	while(1){
		cout << "[rshell] $ ";

		getline(cin, userInput);
		args[0] = (char*)userInput.c_str();
		args[1] = NULL;

		if (userInput == "exit"){
			break;
		}else{
			execute(args);
		}
	}

	return 0;
}
