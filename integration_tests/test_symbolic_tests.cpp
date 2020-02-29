#ifndef __TEST_SYMBOLIC_TESTS_CPP__
#define __TEST_SYMBOLIC_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

TEST (TestSymbolicTest, FullDirectoryAND){
        Tokenizer * tokeniz = new Tokenizer("[ -e header/andToken.hpp ]  && echo \"path exists\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestSymbolicTests, FullDirectoryOR){
        Tokenizer * tokeniz = new Tokenizer("[ -d ../CMakeLists.txt ]  || echo \"not a directory\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestSymbolicTests, SemiColon){
        Tokenizer * tokeniz = new Tokenizer("[ -f integration_tests.cpp  ]; echo \"something\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestSymbolicTests, TwoTests){
        Tokenizer * tokeniz = new Tokenizer("[ -d path/to/file ] || test integration_tests/test_literal_tests.cpp");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestSymbolicTests, invalidSpacing){
        Tokenizer * tokeniz = new Tokenizer("[-e ../rshell]");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (TestSymbolicTests, edgeCaseWhiteSpaces){
        Tokenizer * tokeniz = new Tokenizer("    [    -e        .gitignore ] ;     [   -d   ../assignment-jorr ] &&       [ -f           3 ]");;
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

#endif
