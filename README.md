# CS 100 Programming Project
Winter 2020\
Juvenal Ortega SID: 862154960\
Robert Rivera SID: 862086500

# Introduction
Our program will accomplish the following: print a command prompt, read in a line of command(s) and connector(s) from standard input, execute the appropriate commands using fork, stat, execvp, and waitpid, and repeat until an exit command is executed. The program is designed using composite design pattern, utilizing the following classes: Tokenizer, Executor, and Token which will have various subclasses. The client, R'Shell, will take a command input which will be used to instantiate a Tokenizer object. The Tokenzier object will parse and split the input using boost library with regex, and create a vector of type string with the input in prefix notation. The Tokenizer object will pass the string vector to an Executor object which will create a tree of Token*. Once the tree is created, the executor object can take advantage of polymorphism and execute the tree by executing the root Token.
# Diagram
![](https://raw.githubusercontent.com/cs100/assignment-jorr/master/images/CS%20100%20Assignment%20OMT_%20Class%20Diagram.png?token=AIV3NNNNCTLNSFGHEOK3YSC6KRSUC)

# Classes
**Abstract Token Class:**\
This class will be used to define some common behavior that can be inherited by multiple subclasses. In this case, the multiple subclasses will be the different tokens rshell will use such as connectors and commands. The Token class has pure virtual functions execute, isLeaf, getLeft, getRight, setLeft and setRight.

**CmdToken:**\
This class will be a subclass of the Token class. It will have an array of char* that will hold executable, arguments and flags (e.g. "ls -a, mkdir directory). It will define the execute function from the Token class to use execvp, fork, and waitpid system calls to execute commands. Cmdtokens are leaf objects and as such will point to nullptrs for its left and right objects, as well as leaving setLeft and setRight inactive.

**TestToken:**
This class will be a subclass of the Token class. It will take a string in test format (e.g. test -e file/to/path or [ -e file/to/path ] in its constructor. It will define the execute function from the Token class to use the stat system calls to execute test commands. Testtokens are leaf objects and as such will point to nullptrs for its left and right objects, as well as leaving setLeft and setRight inactive.

**andToken:**\
This class will be a subclass of the Token class. It will receive two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the "&&" connector behavior of a shell. Andtokens are composite objects and such will define setLeft, getLeft, setRight and getRight to be able to interact with other connectors and commands.

**orToken:**\
This class will be a subclass of the Token class. It will receive two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the "||" connector behavior of a shell. OrTokens are composite objects and such will define setLeft, getLeft, setRight and getRight to be able to interact with other connectors and commands.

**semiColonToken:**\
This class will be a subclass of the Token class. It will receive one or two objects of type Token when instantiated. It will define the execute function from the Token class to simulate the ";" connector behavior of a shell.  Semitokens are composite objects and such will define setLeft, getLeft, setRight and getRight to be able to interact with other connectors and commands.


**Tokenizer Class:**\
This class will receive the command input of type string. It will utilize boost library with regex to parse through the input and push them into an argument string vector. The Tokenizer class will also have a shuntingYardAlgorithm function available, where it will rearrange the content of the string vector into prefix notation. The argument string vector will be used to instantiate an Executor object. 
 
 **Executor Class:**\
The executor class will receive an argument vector of type string in its constructor. It will then create Tokens of appropriate type and push them into a Token vector, which it will use to create a tree with proper precedence.  It will then take advantage of inheritance and polymorphism to call the tokens' execute functions. 

# Prototypes/Research
**Commands:**\
While using execvp() we found that it takes input of type char*. Going forward, we will be using string to take in the command which will have to be converted into type char*. When testing the command with values, it was important for the last argument to be NULL. When execvp executed a command, it closed the program which is undesirable as the rshell has to execute commands until exit is called. To avoid this, the fork() command is used. Fork() creates a child process identical to the original parent process. We will use the child process to execute any execvp commands, which will end the child process but not the parent process. This allows us to use execvp in loops to continue to execute commands until exit is called. To avoid nondeterministic behavior, we use waitpid() system call in the parent process to halt the parent process until the child terminates. This is accomplished using waitpid and the WUNTRACED flag. 

**Parsing:**\
The method of parsing we chose to use is boost library with regex. To get boost library to work, it is important to link the proper libraries in CMakeLists.txt. Once working, we created regular expressions and use regex_search to find any matches from our input string. As of now, we only have regular expressions to detect connectors and executables. Because regex_search stops after its first match, we had to find a way for regex_search to find all matches. We ended up using the boost::smatch type to hold any matches found by regex_search. Boost’s smatch also has a built in function: suffix() which allows us to cut off the parts of the input string that have already been searched, by setting the string equal to smatch.suffix(). For example, if we were looking for connectors and our input string is “mkdir && ls ;” It would remove “mkdir &&” after it matches with &&, leaving only “ls ;” for the next search. Of course, this came with the consequence of destroying the input string, which we still needed to search for executable and argument parsing. Our current work around is to declare temporary strings equal to input string, with the intention of using them in place of the input string so the original stays intact. Our solutions for parsing may cause problems as the rshell will be more complex than the prototype functions, and as such we will be looking to improve our parsing method. 

**Connectors:**\
While investigating the connector behavior, we found that a command shell reads the input from left to right, unless parenthesis are used. When || is used, the shell will execute the left side first, after which it may execute the right side but only if the left side failed. When using && the shell will attempt to execute both sides of the input but will stop if the left side fails. With the ; connector, it is similar to && but will attempt to execute even if the left side of the input fails. When using these three in conjunction, the shell reads the input from left to right and behaves as expected.
# Development and Testing Roadmap
1. Awaiting assigment 4
