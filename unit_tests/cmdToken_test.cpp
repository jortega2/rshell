#ifndef __CMD_TEST_CPP__
#define __CMD_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/cmdToken.hpp"


//cmdToken receivs input that has already been heavily parsed by Tokenizer.
//cmdToken should never receive a command with a connector, comment, or an input that is more 
//than one executable (e.g. it will never receive ls -a echo pog) unless it is in quotes. 
//cmdToken will typically receive input in the form "executable argument(s)" which it will take and split up
//delete necessary whitespace (unless in quotes), remove quotes (e.g. echo "poggers" will output poggers not "poggers")
//anything else is outside the scope of cmdToken and should have been handled  by Tokenizer. 

//Note: execute function will return 0 if execvp throws in error.
//execute will return 1 if no error is detected.

TEST (cmdTokenParse, genericCommmand) {
	std::vector <std::string> expected {"ls", "-a"};
	CmdToken* test = new CmdToken("ls -a");
	EXPECT_EQ(test->returnVector(), expected);
}

TEST (cmdTokenParse, HandlesWhiteSpace) {
        std::vector <std::string> expected {"ls", "-a"};
        CmdToken* test = new CmdToken("       ls         -a        ");
        EXPECT_EQ(test->returnVector(), expected);
}

TEST (cmdTokenParse, HandlesQuotes) {
        std::vector <std::string> expected {"echo", "    testing testing 1 2 3    "};
        CmdToken* test = new CmdToken("echo\"    testing testing 1 2 3    \"");
        EXPECT_EQ(test->returnVector(), expected);
}

TEST (CmdTokenTest, ls){
	CmdToken* test = new CmdToken("ls");
	EXPECT_EQ(test->execute(), 1); 
}

TEST (CmdTokenTest, lsj){
        CmdToken* test = new CmdToken("ls -j");
        EXPECT_EQ(test->execute(), 0);
}

TEST (CmdTokenTest, bigEcho){
        CmdToken* test = new CmdToken("echo parsing parsing 1 2 3 i love parsing");
        EXPECT_EQ(test->execute(), 1);
}

TEST (CmdTokenTest, pwdAndWhiteSpace){
        CmdToken* test = new CmdToken("       pwd            ");
        EXPECT_EQ(test->execute(), 1);
}

TEST (CmdTokenEdgeCase, invalidCommand ){
        CmdToken* test = new CmdToken("echa parsing parsing 1 2 3 i love parsing");
        EXPECT_EQ(test->execute(), 0);
}

TEST (CmdTokenEdgeCase, smashedKeyboardInput){
        CmdToken* test = new CmdToken("adjqnqildl13jgligmk2mng1@*!&Fnlkavekg3");
        EXPECT_EQ(test->execute(), 0);
}

TEST (CmdTokenEdgeCase, NoInput){
        CmdToken* test = new CmdToken("");
        EXPECT_EQ(test->execute(), 1);
}

TEST (CmdTokenEdgeCase, InputC){
	CmdToken* test = new CmdToken("^C");
	EXPECT_EQ(test->execute(), 0);
}

#endif
