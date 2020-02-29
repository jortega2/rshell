#ifndef __EXIT_COMMAND_TESTS_CPP__
#define __EXIT_COMMAND_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

//note: my exit command triggers in the exec->exeute() and the ./test executable stops after the first test block.
//so the expect_eq function technically never finishes, but you can see the proper functionality when you run .tests
//for example, echo test && exit will close the test exec but you can see "hello" before it does so. 
//all these tests work and you can test them by having only one active at a time (e.g. comment all but 1 test block)
//the tests that are commented out are tests that SHOULD exit, otherwise they shouldn't because misout or connector logic (e.g. ech 1 && exit doesn't exit)



TEST (ExitCommandTests, ORexit){
        Tokenizer * tokeniz = new Tokenizer("echo hey || exit");
	tokeniz->parse();
	tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (ExitCommandTests, pwdORexitORexit){
        Tokenizer * tokeniz = new Tokenizer("pwd ||  exit ||   exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (ExitCommandTests, UpperCaseExit){
        Tokenizer * tokeniz = new Tokenizer("EXIT");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (ExitCommandTests, fiveCommandsExit){
        Tokenizer * tokeniz = new Tokenizer("echo 1 && echo 2 || exit ;  echo 1");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (ExitCommandTests, invalidConnectorsExit){
        Tokenizer * tokeniz = new Tokenizer(" pwd && && exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

/*TEST (ExitCommandTests, ANDwithWhiteSpace){
        Tokenizer * tokeniz = new Tokenizer("echo hey &&       exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}*/

/*TEST (ExitCommandTests, simpleExit){
        Tokenizer * tokeniz = new Tokenizer("exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}*/

/*TEST (ExitCommandTests, semicolonExit){
        Tokenizer * tokeniz = new Tokenizer("echo hey ;       exit ;");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}*/

/*TEST (ExitCommandTests, invalidORexit){
        Tokenizer * tokeniz = new Tokenizer("echaz hey || exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}*/


#endif
