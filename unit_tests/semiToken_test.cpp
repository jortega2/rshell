#ifndef __SEMITOKEN_TESTS_CPP__
#define __SEMITOKEN_TESTS_CPP__
#include "../header/semiToken.hpp"
#include "gtest/gtest.h"
#include "../header/cmdToken.hpp"

//Note: execute function will return 0 if execvp throws in error.
//execute will return 1 if no error is detected.

TEST (SemiColonTwoCommand, validSCvalid){
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	SemiToken* test = new SemiToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
	EXPECT_EQ(test->stringify(), "ls ; echo success");
}

TEST (SemiColonTwoCommand, invalidSCvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("echo pog");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "pog ; echo pog");
}

TEST (SemiColonTwoCommand, validSCinvalid){
        CmdToken* left = new CmdToken("echo pog");
        CmdToken* right = new CmdToken ("pog");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "echo pog ; pog");
}

TEST (SemiColonTwoCommand, invalidSinCvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "pog ; gers");
}

TEST (SemiColonTokenTest, emptyConnectorTest) {
        CmdToken* left = new CmdToken("ls");
        CmdToken* right = new CmdToken("pwd");
        SemiToken* test = new SemiToken();
        test->setLeft(left);
        test->setRight(right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls ; pwd");
}

TEST (SemiColonTokenTest, EmptyNodesTest) {
        CmdToken* right = new CmdToken("ls");
        SemiToken* test = new SemiToken();
        test->setRight(right);
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "");
}

#endif
