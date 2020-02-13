#ifndef __ORTOKEN_TEST_HPP__
#define __ORTOKEN_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/orToken.hpp"
#include "../header/cmdToken.hpp"

TEST (orTokenTest, lsORechoSuccess){
	//ls || echo sucess
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	OrToken* test = new OrToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
}

TEST (orTokenTest, invalidORvalid){
	// ls -j || echo failure
        CmdToken* left = new CmdToken("ls -j");
        CmdToken* right = new CmdToken ("echo failure");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
}

TEST (orTokenTest, validORinvalid){
	//ls || echa ?
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("echa ?");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
}

TEST (orTokenTest, invalidORinvalid){
	//pog || gers
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (orTokenTest, nestedOr){
	//pwd || ls || pwd
	CmdToken* left = new CmdToken("pwd");
        CmdToken* right = new CmdToken ("ls");
	CmdToken* right2 = new CmdToken ("pwd"); 
	OrToken* nested = new OrToken(left,right);
        OrToken* test = new OrToken(nested, right2);
        EXPECT_EQ(test->execute(), 1);
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
}
TEST (orTokenTest, validORkeyboardsmash){
	// ls || adlakwjfaigjalkga
	CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("afiajgjf1jt1g");
        OrToken* test = new OrToken(left, right);
        EXPECT_EQ(test->execute(), 1);
}

#endif