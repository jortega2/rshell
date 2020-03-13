#ifndef __PIPE_TEST_CPP__
#define __PIPE_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/pipeToken.hpp"
#include "../header/cmdToken.hpp"

/*`TEST (pipeTokenTest, genericCommmand) {
	CmdToken * left = new CmdToken ("cat prototype/something.txt");
	CmdToken * right = new CmdToken ("tr a-z A-Z");
	PipeToken * test = new PipeToken( left, right);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "cat prototype/something.txt | tr a-z A-Z");
}

TEST (pipeTokenTest, genericCommmand2) {
        CmdToken * left = new CmdToken ("ls -l");
	CmdToken * right = new CmdToken ("more");
        PipeToken * test = new PipeToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls -l | more");
}

TEST (pipeTokenTest, nestedPipe) {
        CmdToken * left = new CmdToken ("cat prototype/something.txt | head -7");
	CmdToken * right = new CmdToken ("tail -5");
	PipeToken * test = new PipeToken(left, right);
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "cat prototype/something.txt | head -7 | tail -5");
}

TEST (pipeTokenTest, geeksforgeeksCommand){
	CmdToken * left = new CmdToken("ls -l");
	CmdToken * right = new CmdToken("find ./ -type f -name \"*.txt\" -exec grep \"program\" {} \\;");
	PipeToken * test = new PipeToken(left, right);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "ls -l | find ./ -type f -name \"*.txt\" -exec grep \"program\" {} \\;");
}

TEST (pipeTokenTest, greeksforgeeksNestedAlt){
	CmdToken * left = new CmdToken("cat prototype/something.txt");
	CmdToken * right = new CmdToken("grep \"Margie\"");
	CmdToken * right2 =  new CmdToken( "tee file2.txt");
	CmdToken * right3 = new CmdToken( "wc -l");
	PipeToken * pipe = new PipeToken(left, right);
	PipeToken * pipe1 = new PipeToken(pipe, right2);
	PipeToken * test = new PipeToken(pipe1, right3);
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "cat prototype/something.txt | grep \"Margie\" | tee file2.txt | wc -l");

	//delete file2.txt (not needed)
	CmdToken * cmd = new CmdToken("rm file2.txt");
	cmd->execute();
}*/

TEST (pipeTokenTest, pipeIntoMissingDir) {
        CmdToken * left = new CmdToken ("ls -l");
	CmdToken * right = new CmdToken("prototype/poggies");
	PipeToken * test = new PipeToken(left, right);
        EXPECT_EQ(test->execute(), 0);
        EXPECT_EQ(test->stringify(), "ls -l | prototype/poggies");
}

TEST (pipeTokenTest, pipeIntoFileErrorCheck) {
        CmdToken * left = new CmdToken ("ls -l");
	CmdToken * right = new CmdToken("poggers");
	PipeToken * test = new PipeToken(left, right);
        EXPECT_EQ(test->execute(), 0);
        EXPECT_EQ(test->stringify(), "ls -l | poggers");
}

/*TEST (pipeTokenTest, invalidCmd) {
        CmdToken * left = new CmdToken ("ls -j");
	CmdToken * right = new CmdToken ("tr a-z A-Z");
	PipeToken * test = new PipeToken(left, right);
        EXPECT_EQ(test->execute(), 1);
        EXPECT_EQ(test->stringify(), "ls -j | tr a-z A-Z");
}*/

#endif
