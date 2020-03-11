#ifndef __ORTOKEN_TEST_CPP__
#define __ORTOKEN_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/orToken.hpp"
#include "../header/cmdToken.hpp"

//Note: execute function will return 0 if execvp throws in error.
//execute will return 1 if no error is detected.

TEST (orTokenTest, lsORechoSuccess){
	//ls || echo sucess
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	OrToken* test = new OrToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
	EXPECT_EQ(test->stringify(), "ls || echo success");
}

TEST (orTokenTest, invalidORvalid){
	// ls -j || echo failure
        CmdToken* left = new CmdToken("ls -j");
        CmdToken* right = new CmdToken ("echo failure");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls -j || echo failure");
}

TEST (orTokenTest, validORinvalid){
	//ls || echa ?
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("echa ?");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls || echa ?");
}

TEST (orTokenTest, invalidORinvalid){
	//pog || gers
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "pog || gers");
}

TEST (orTokenTest, nestedOr){
	//pwd || ls || pwd
	CmdToken* left = new CmdToken("pwd");
        CmdToken* right = new CmdToken ("ls");
	CmdToken* right2 = new CmdToken ("pwd"); 
	OrToken* nested = new OrToken(left,right);
        OrToken* test = new OrToken(nested, right2);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "pwd || ls || pwd");
}

TEST (orTokenTest, doubleNestedOr){
	//pwd || ls || pwd || ls
	CmdToken* left = new CmdToken("pwd");
        CmdToken* right = new CmdToken ("ls");
        CmdToken* right2 = new CmdToken ("rm -rf zfolder");
        OrToken* nested1 = new OrToken(left,right);
	OrToken* nested2 = new OrToken(nested1, right2);
        OrToken* test = new OrToken(nested2, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "pwd || ls || rm -rf zfolder || ls");
}
TEST (orTokenTest, validORkeyboardsmash){
	// ls || adlakwjfaigjalkga
	CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("afiajgjf1jt1g");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls || afiajgjf1jt1g");
}

TEST (orTokenTest, emptyConnectorTest) {
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken("pwd");
        OrToken* test = new OrToken();
        test->setLeft(left);
        test->setRight(right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls || pwd");
}

TEST (orTokenTest, EmptyNodeTest) {
        CmdToken* left = new CmdToken("ls");
        OrToken* test = new OrToken();
        test->setLeft(left);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "");
}

#endif
