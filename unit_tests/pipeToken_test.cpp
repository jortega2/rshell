#ifndef __PIPE_TEST_CPP__
#define __PIPE_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/pipeToken.hpp"
#include "../header/cmdToken.hpp"

TEST (pipeTokenTest, genericCommmand) {
	CmdToken * left = new CmdToken ("cat prototype/something.txt");
	PipeToken * test = new PipeToken("| tr a-z A-Z", left);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "cat prototype/something.txt | tr a-z A-Z");
}

TEST (pipeTokenTest, genericCommmand2) {
        CmdToken * left = new CmdToken ("ls -l");
        PipeToken * test = new PipeToken("| more", left);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls -l | more");
}

TEST (pipeTokenTest, nestedPipe) {
        CmdToken * left = new CmdToken ("cat prototype/something.txt | head -7");
        PipeToken * test = new PipeToken("| tail -5", left);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "cat prototype/something.txt | head -7 | tail -5");
}

TEST (pipeTokenTest, geeksforgeeksCommand){
	CmdToken * left = new CmdToken("ls -l");
	PipeToken * test = new PipeToken ("| find ./ -type f -name \"*.txt\" -exec grep \"program\" {} \\;", left);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls -l | find ./ -type f -name \"*.txt\" -exec grep \"program\" {} \\;");
}

TEST (pipeTokenTest, greeksforgeeksNestedAlt){
	CmdToken * left = new CmdToken("cat prototype/something.txt");
	PipeToken * one = new PipeToken(" | grep \"Margie\"", left);
	PipeToken * two = new PipeToken(" | tee file2.txt", one);
	PipeToken * test = new PipeToken(" | wc -l", two);
	EXPECT_EQ(test->execute(), 1);
	
	//delete file2.txt (not needed)
	CmdToken * cmd = new CmdToken("rm file2.txt");
	cmd->execute();
}
#endif
