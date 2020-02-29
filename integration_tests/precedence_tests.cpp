#ifndef __PRECEDENCE_TESTS_CPP__
#define __PRECEDENCE_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"
#include "../header/orToken.hpp"
#include "../header/semiToken.hpp"

TEST (PrecedenceTest, singleSet){
        Tokenizer * tokeniz = new Tokenizer(" (echo A && echo B ) ||  echo C ");
        tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (PrecedenceTest, SampleCommand ){
        Tokenizer * tokeniz = new Tokenizer(" (echo A && echo B ) || ( echo C && echo D )");
        tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (PrecedenceTest, singleSetNested){
        Tokenizer * tokeniz = new Tokenizer("echo A ; echo B && ( echo C || echo D ) && echo E");
        tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (PrecedenceTest, doubleSetNested){
        Tokenizer * tokeniz = new Tokenizer(" (test -e dif || echo A ) && echo B ; ( echa C || echo D ) ; echo E");
        tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (PrecedenceTest, fiveSets){
        Tokenizer * tokeniz = new Tokenizer("(echo 1 && echo 2) && ( echo 3 ; echo 4) && echo 5 && echo 6 && (echo 7 || echo &) && (echo 9)");
        tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

#endif
