#ifndef __MULTIPLE_COMMAND_TESTS_CPP__
#define __MULTIPLE_COMMAND_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"
#include "../header/orToken.hpp"
#include "../header/semiToken.hpp"

TEST (MultipleCommandTests, AND){
        Tokenizer * tokeniz = new Tokenizer("echo hey && echo there");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, OR){
        Tokenizer * tokeniz = new Tokenizer("echo hey || echo there");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, SemiColon){
        Tokenizer * tokeniz = new Tokenizer("echo hey ; echo there");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, ORnAND){
        Tokenizer * tokeniz = new Tokenizer("echo 1 || echo 2 && pwd");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, ANDnSemiColon){
        Tokenizer * tokeniz = new Tokenizer("ls && pwd ;");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, edgeCaseWhiteSpace3Connectors){
        Tokenizer * tokeniz = new Tokenizer("     echo        1 ;        echo    2 &&          echo        3 || echo               4");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (MultipleCommandTests, edgeCaseTooManyConnectors){
        Tokenizer * tokeniz = new Tokenizer("echo hey && echo there && " );
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (MultipleCommandTests, edgeCaseConnectorsOnly){
        Tokenizer * tokeniz = new Tokenizer("&& || ;");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (MultipleCommandTests, assignment2SampleCommand){
        Tokenizer * tokeniz = new Tokenizer("ls -a; echo hello && mkdir ztest && rm -rf ztest || echo world ; git status");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

#endif