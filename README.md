# CS 100 Programming Project
Winter 2020\
Juvenal Ortega SID: 862154960\
Robert Rivera SID: 862086500

# Introduction
Our program will accomplish the following: print a command prompt, read in a line of command(s) and connector(s) from standard input, execute the appropriate commands using fork, execvp, and waitpid, and repeat until an exit command is executed. The program is designed using composite design pattern, utilizing the following classes: Tokenizer, Executor, and Token which will have various subclasses. The client, R'Shell, will take a command input which will be used to instantiate a Tokenizer object. The Tokenzier object will parse and split the input using boost library with regex, and create appropriate Token objects. The token objects utilize polymorphism to define their own execute() function, involving execvp, fork and waitpid. The Tokenizer object will setup a vector of type Token* that will be passed to an Executor object that will call the Tokens' execute() function. 

# Diagram
![](https://raw.githubusercontent.com/cs100/assignment-jorr/master/images/CS%20100%20Assignment%20OMT_%20Class%20Diagram.png?token=AIV3NNNNCTLNSFGHEOK3YSC6KRSUC)

# Classes
**Abstract Token Class:**\
This class will be used to define some common behavior that can be inherited by multiple subclasses. In this case, the multiple subclasses will be the different inputs (we will call them tokens) a user can enter such as executables, arguments, and connectors. The Token class will have a pure virtual function "execute" which will be defined by its subclasses.

**CmdToken:**\
This class will be a subclass of the Token class. It will have an array of char* that will hold executable, arguments and flags (e.g. "ls -a, mkdir directory). It will define the execute function from the Token class to use execvp, fork, and waitpid system calls to execute commands. 

**andToken:**\
This class will be a subclass of the Token class. It will receive two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the "&&" connector behavior of a shell. 

**orToken:**\
This class will be a subclass of the Token class. It will receive two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the "||" connector behavior of a shell.

**semiColonToken:**\
This class will be a subclass of the Token class. It will receive one or two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the ";" connector behavior of a shell.


**Tokenizer Class:**\
This class will receive the command input of type string. It will utilize boost library with regex to parse through the input and push them into argument and connector string vectors. These vectors will be used to instantiate any executor object.
 
 **Executor Class:**\
The executor class will receive an argument and connector vectors of type string in its constructor. It will then create Tokens of appropritate type and push them into a Token vector. It will then take advantage of inheritance and polymorphism to call the tokens' execute functions. 

# Prototypes/Research
**Commands:**\
While using execvp() we found that it takes input of type char*. Going forward, we will be using string to take in the command which will have to be converted into type char*. When testing the command with values, it was important for the last argument to be NULL. When execvp executed a command, it closed the program which is undesirable as the rshell has to execute commands until exit is called. To avoid this, the fork() command is used. Fork() creates a child process identical to the original parent process. We will use the child process to execute any execvp commands, which will end the child process but not the parent process. This allows us to use execvp in loops to continue to execute commands until exit is called. To avoid nondeterministic behavior, we use waitpid() system call in the parent process to halt the parent process until the child terminates. This is accomplished using waitpid and the WUNTRACED flag. 

**Parsing:**\
The method of parsing we chose to use is boost library with regex. To get boost library to work, it is important to link the proper libraries in CMakeLists.txt. Once working, we created regular expressions and use regex_search to find any matches from our input string. As of now, we only have regular expressions to detect connectors and executables. Because regex_search stops after its first match, we had to find a way for regex_search to find all matches. We ended up using the boost::smatch type to hold any matches found by regex_search. Boost’s smatch also has a built in function: suffix() which allows us to cut off the parts of the input string that have already been searched, by setting the string equal to smatch.suffix(). For example, if we were looking for connectors and our input string is “mkdir && ls ;” It would remove “mkdir &&” after it matches with &&, leaving only “ls ;” for the next search. Of course, this came with the consequence of destroying the input string, which we still needed to search for executable and argument parsing. Our current work around is to declare temporary strings equal to input string, with the intention of using them in place of the input string so the original stays intact. Our solutions for parsing may cause problems as the rshell will be more complex than the prototype functions, and as such we will be looking to improve our parsing method. 

**Connectors:**\
While investigating the connector behavior, we found that a command shell reads the input from left to right, unless parenthesis are used. When || is used, the shell will execute the left side first, after which it may execute the right side but only if the left side failed. When using && the shell will attempt to execute both sides of the input but will stop if the left side fails. With the ; connector, it is similar to && but will attempt to execute even if the left side of the input fails. When using these three in conjunction, the shell reads the input from left to right and behaves as expected.
# Development and Testing Roadmap
1. [Create Token Class](https://github.com/cs100/assignment-jorr/issues/1)
1. [Create cmdToken Class](https://github.com/cs100/assignment-jorr/issues/2)
1. [Create Tokenizer Class](https://github.com/cs100/assignment-jorr/issues/3)
1. [Update and test parsing function](https://github.com/cs100/assignment-jorr/issues/4)
1. [Create Executor Class](https://github.com/cs100/assignment-jorr/issues/5)
1. [Fix exit bug](https://github.com/cs100/assignment-jorr/issues/6)
1. [Test program with commands, arguments, and flags (no connectors)](https://github.com/cs100/assignment-jorr/issues/7)
1. [Create andToken Class, implement into Tokenizer](https://github.com/cs100/assignment-jorr/issues/8)
1. [Test program for proper "&&" functionality ](https://github.com/cs100/assignment-jorr/issues/9)
1. [Create semiColonToken Class, implement into Tokenizer](https://github.com/cs100/assignment-jorr/issues/10)
1. [Test program for proper ";" functionality](https://github.com/cs100/assignment-jorr/issues/11)
1. [Test program with multiple connectors (both && and ;)](https://github.com/cs100/assignment-jorr/issues/12)
1. [Create orToken Class, implement into Tokenizer](https://github.com/cs100/assignment-jorr/issues/13)
1. [Test for proper "||" functionality](https://github.com/cs100/assignment-jorr/issues/14)
1. [Testing for multiple connectors, arguments, flags](https://github.com/cs100/assignment-jorr/issues/15)
1. [Finalize Unit Tests](https://github.com/cs100/assignment-jorr/issues/16)
1. [Finalize Integration Tests](https://github.com/cs100/assignment-jorr/issues/17)
