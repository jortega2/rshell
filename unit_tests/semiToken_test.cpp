#ifndef __SEMITOKEN_TESTS_HPP__
#define __SEMITOKEN_TESTS_HPP__
#include "../header/semiToken.hpp"
#include "gtest/gtest.h"
#include "../header/cmdToken.hpp"

TEST (SemiColonTwoCommand, validSCvalid){
	CmdToken* left = new CmdToken("ls");
	CmdToken* right = new CmdToken ("echo success");
	SemiToken* test = new SemiToken(left, right);
	EXPECT_EQ(test->execute(), 1); 
}

TEST (SemiColonTwoCommand, invalidSCvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("echo pog");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 1);
}

TEST (SemiColonTwoCommand, validSCinvalid){
        CmdToken* left = new CmdToken("echo pog");
        CmdToken* right = new CmdToken ("pog");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (SemiColonTwoCommand, invalidSinCvalid){
        CmdToken* left = new CmdToken("pog");
        CmdToken* right = new CmdToken ("gers");
        SemiToken* test = new SemiToken(left, right);
        EXPECT_EQ(test->execute(), 0);
}

TEST (SemiColonOneCommand, validSC){
        CmdToken* left = new CmdToken("ls");
        SemiToken* test = new SemiToken(left);
        EXPECT_EQ(test->execute(), 1);
}

TEST (SemiColonOneCommand, invalidSC){
        CmdToken* left = new CmdToken("ls -j");
        SemiToken* test = new SemiToken(left);
        EXPECT_EQ(test->execute(), 0);
}

TEST (SemiColonOneCommand, nullSC){
        CmdToken* left = new CmdToken("");
        SemiToken* test = new SemiToken(left);
        EXPECT_EQ(test->execute(), 1);
}




#endif
