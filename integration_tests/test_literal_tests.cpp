#ifndef __TEST_LITERAL_TESTS_CPP__
#define __TEST_LITERAL_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

TEST (TestLiteralTest, FullDirectoryAND){
        Tokenizer * tokeniz = new Tokenizer("test -e header/andToken.hpp  && echo \"path exists\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestLiteralTests, FullDirectoryOR){
        Tokenizer * tokeniz = new Tokenizer(" test -d ../CMakeLists.txt || echo \"not a directory\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestLiteralTests, SemiColon){
        Tokenizer * tokeniz = new Tokenizer("test -f integration_tests.cpp ; echo \"something\"");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestLiteralTests, TwoTests){
        Tokenizer * tokeniz = new Tokenizer("test -d path/to/file  || test integration_tests/test_literal_tests.cpp");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (TestLiteralTests, invalidExitCapilization){
        Tokenizer * tokeniz = new Tokenizer("TEST -e rshell");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (TestLiteralTests, edgeCaseWhiteSpaces){
        Tokenizer * tokeniz = new Tokenizer("     test -e        .gitignore ;        test -d   ../assignment-jorr  &&          test -f           3");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

#endif
