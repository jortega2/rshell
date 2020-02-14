#ifndef __SINGLE_COMMAND_TESTS_CPP__
#define __SINGLE_COMMAND_TESTS_CPP__
#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"
#include "../header/Executor.hpp"
#include "../header/cmdToken.hpp"
#include "../header/andToken.hpp"
#include "../header/orToken.hpp"
#include "../header/semiToken.hpp"

TEST (SingleCommandTests, ls){
	Tokenizer * tokeniz = new Tokenizer("ls");
	Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
	EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, lsSEMICOLON){
        Tokenizer * tokeniz = new Tokenizer("ls ;");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, pwdWhitespace){
        Tokenizer * tokeniz = new Tokenizer("     pwd      ");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, echoQuotes){
        Tokenizer * tokeniz = new Tokenizer("echo \"&& || ; #\"");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, gitStatus){
        Tokenizer * tokeniz = new Tokenizer("git status");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, mkdirZTEST){
        Tokenizer * tokeniz = new Tokenizer("mkdir ZTEST");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, deleteZTEST){
        Tokenizer * tokeniz = new Tokenizer("rm -rf ZTEST");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
	exec->isValid();
	exec->createTokens();
        EXPECT_EQ(exec->execute(), 1);
}

TEST (SingleCommandTests, invalidCommand1){
        Tokenizer * tokeniz = new Tokenizer("ls -j");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (SingleCommandTests, invalidCommand2){
        Tokenizer * tokeniz = new Tokenizer("pog");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

TEST (SingleCommandTests, invalidCommand3){
        Tokenizer * tokeniz = new Tokenizer("makedirectory ls");
        Executor * exec = new Executor (tokeniz->returnArgs(), tokeniz->returnConns());
        exec->isValid();
        exec->createTokens();
        EXPECT_EQ(exec->execute(), 0);
}

#endif
