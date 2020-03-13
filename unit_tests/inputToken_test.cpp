#ifndef __INPUTTOKEN_TEST_CPP__
#define __INPUTTOKEN_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/inputToken.hpp"
#include "../header/cmdToken.hpp"

/*TEST (inputTokenTest, genericCommmand) {
	CmdToken * left =  new CmdToken("tr a-z A-Z");
	CmdToken * right = new CmdToken("some.txt");
	InputToken * test = new InputToken(left, right);
	EXPECT_EQ(test->stringify(), "tr a-z A-Z < some.txt");
	EXPECT_EQ(test->execute(), 1);
}*/

TEST (inputTokenTest, incorrectCommmand) {
        CmdToken * left =  new CmdToken("poggers");
        CmdToken * right = new CmdToken("some.txt");
        InputToken * test = new InputToken(left, right);
        EXPECT_EQ(test->stringify(), "poggers < some.txt");
        EXPECT_EQ(test->execute(), 0);
}

/*TEST (inputTokenTest, MissingFile) {
        CmdToken * left =  new CmdToken("tr a-z A-Z");
        CmdToken * right = new CmdToken("poggers");
        InputToken * test = new InputToken(left, right);
        EXPECT_EQ(test->stringify(), "tr a-z A-Z < poggers");
        EXPECT_EQ(test->execute(), 0);
}

TEST (inputTokenTest, nestedCommand) {
        CmdToken * left =  new CmdToken("tr a-z A-Z");
        CmdToken * right = new CmdToken("some.txt");
	CmdToken * left2 = new CmdToken("sort");
        InputToken * input = new InputToken(left, right);
	InputToken * test = new InputToken(left2, input);
        EXPECT_EQ(test->stringify(), "sort < tr a-z A-Z < some.txt");
        EXPECT_EQ(test->execute(), 0);
}*/


#endif
