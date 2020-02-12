#ifndef __CMD_TEST_HPP__
#define __CMD_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/cmdToken.hpp"
#include "../src/cmdToken.cpp"
#include "unistd.h"

TEST (cmdTokenTest, genericCommmand) {
	std::vector <std::string> expected {"ls", "-a"};
	CmdToken* test = new CmdToken("ls -a");
	EXPECT_EQ(test->returnVector(), expected);
}

TEST (cmdTokenTest, HandlesWhiteSpace) {
        std::vector <std::string> expected {"ls", "-a"};
        CmdToken* test = new CmdToken("       ls         -a        ");
        EXPECT_EQ(test->returnVector(), expected);
}

TEST (cmdTokenTest, HandlesQuotes) {
        std::vector <std::string> expected {"echo", "    testing testing 1 2 3    "};
        CmdToken* test = new CmdToken("echo\"    testing testing 1 2 3    \"");
        EXPECT_EQ(test->returnVector(), expected);
}

/*TEST (CmdTokenText, OneCommand){
	char *command[1];
	std::string ls = "ls";
	command[0] = (char*)ls.c_str();
	command[1] = NULL;
	CmdToken* test = new CmdToken("ls");
	EXPECT_EQ((execvp(command[0], command)), test->execute()); 
}*/

#endif
