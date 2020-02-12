#ifndef __ANDTOKEN_TEST_HPP__
#define __ANDTOKEN_HPP_TEST__

#include "gtest/gtest.h"
#include "../header/andToken.hpp"
#include "../header/cmdToken.hpp"

TEST (andTokenTest, lsANDechoSuccess){
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	AndToken* test = new AndToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
}

TEST (andTokenTest, invalidANDvalid){
        CmdToken* left = new CmdToken("ls -j");
        CmdToken* right = new CmdToken ("echo failure");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (andTokenTest, validANDinvalid){
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken ("echa ?");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (andTokenTest, invalidANDinvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        AndToken* test = new AndToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (andTokenTest, nestedAnd){
	//mkdir folder && ls && rm -rf folder
        CmdToken* left = new CmdToken("mkdir folder");
        CmdToken* right = new CmdToken ("ls");
	CmdToken* right2 = new CmdToken ("rm -rf folder"); 
	AndToken* nested = new AndToken(left,right);
        AndToken* test = new AndToken(nested, right2);
        EXPECT_EQ(test->execute(), 1);
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
}




#endif
