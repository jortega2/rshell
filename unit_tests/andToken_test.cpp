#ifndef __ANDTOKEN_TEST_CPP__
#define __ANDTOKEN_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/andToken.hpp"
#include "../header/cmdToken.hpp"

//Note: execute function will return 0 if execvp throws in error.
//execute will return 1 if no error is detected.

TEST (andTokenTest, lsANDechoSuccess){
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	AndToken* test = new AndToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
	EXPECT_EQ(test->stringify(), "ls && echo success");
}

TEST (andTokenTest, invalidANDvalid){
        CmdToken* left = new CmdToken("ls -j");
        CmdToken* right = new CmdToken ("echo failure");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "ls -j && echo failure");
}

TEST (andTokenTest, validANDinvalid){
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("echa ?");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "ls && echa ?");
}

TEST (andTokenTest, invalidANDinvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "pog && gers");
}

TEST (andTokenTest, nestedAnd){
	//mkdir folder && ls && rm -rf folder
        CmdToken* left = new CmdToken("mkdir folder");
        CmdToken* right = new CmdToken ("ls");
	CmdToken* right2 = new CmdToken ("rm -rf folder"); 
	AndToken* nested = new AndToken(left,right);
        AndToken* test = new AndToken(nested, right2);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "mkdir folder && ls && rm -rf folder");
}

TEST (andTokenTest, doubleNestedAnd){
        //mkdir folder && ls && rm -rf folder && ls
        CmdToken* left = new CmdToken("mkdir zfolder");
        CmdToken* right = new CmdToken ("ls");
        CmdToken* right2 = new CmdToken ("rm -rf zfolder");
        AndToken* nested1 = new AndToken(left,right);
	AndToken* nested2 = new AndToken(nested1, right2);
        AndToken* test = new AndToken(nested2, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "mkdir zfolder && ls && rm -rf zfolder && ls");
}

TEST (andTokenTest, emptyConnectorTest) {
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken("pwd");
	AndToken* test = new AndToken();
	test->setLeft(left);
	test->setRight(right);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls && pwd");
}

TEST (andTokenTest, NullNodeTest) {
        CmdToken* left = new CmdToken("ls");
        AndToken* test = new AndToken();
        test->setLeft(left);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "");
}

#endif
