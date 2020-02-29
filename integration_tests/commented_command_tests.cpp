#ifndef __COMMENTED_COMMAND_TESTS_CPP__
#define __COMMENTED_COMMAND_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"

TEST (CommentedCommandTests, lsCommentExit){
        Tokenizer * tokeniz = new Tokenizer("ls #exit");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (CommentedCommandTests, EchoComment){
        Tokenizer * tokeniz = new Tokenizer("echo 1 2 # 3 4 5 6 ");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (CommentedCommandTests, CommentInQuotes){
        Tokenizer * tokeniz = new Tokenizer("echo \"1 2 # 3\" # 4 5 6");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (CommentedCommandTests, commentOnly){
        Tokenizer * tokeniz = new Tokenizer("#comment");
	tokeniz->parse();
        tokeniz->shuntingYardAlgorithm();
        Executor * exec = new Executor (tokeniz->returnArgs());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}
#endif
