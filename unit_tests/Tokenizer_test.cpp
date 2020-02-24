#ifndef __TOKENIZER_TEST_CPP__
#define __TOKENIZER_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"

//note: parser does not fully parse, just parses enough for a cmdToken to do the rest.
//An example of tokenizer parseing would be splitting up "ls -a; echo hello && mkdir test || echo world ; git status"
//into a string vector of {"ls -a", " echo hello ", " mkdir test ", " echo world ", " git status"}

TEST (TokenizerParse, OneCommand) {
	std::vector<std::string> one {"ls -a"};
	Tokenizer* test = new Tokenizer("ls -a");
	EXPECT_EQ(test->returnArgs(), one);
}

TEST (TokenizerParse, TwoCommands) {
	std::vector<std::string> two {"mkdir folder",";","ls -a"};
        Tokenizer* test = new Tokenizer("mkdir folder;ls -a");
        EXPECT_EQ(test->returnArgs(), two);
}

TEST (TokenizerParse, ThreeCommands) {
	std::vector<std::string> three {"mkdir folder", "||", " ls -a ", "&&", " echo here"};
        Tokenizer* test = new Tokenizer("mkdir folder|| ls -a && echo here");
        EXPECT_EQ(test->returnArgs(), three);
}

TEST (TokenizerParse, FourCommands) {
        std::vector<std::string> four {"   mkdir folder ", ";", " ls -a ", "||", " echo here ","&&"," ls"};
	Tokenizer* test = new Tokenizer("   mkdir folder ; ls -a || echo here && ls");
        EXPECT_EQ(test->returnArgs(), four);
}

TEST (TokenizerParse, QuoteCommands) {
        std::vector<std::string> quotes{"mkdir folder","&&", "echo \"&& || ;\""};
	Tokenizer* test = new Tokenizer("mkdir folder&&echo \"&& || ;\"");
        EXPECT_EQ(test->returnArgs(), quotes);
}

TEST (TokenizerParse, CommentCommands) {
	std::vector<std::string> comment{"mkdir folder","||", "echo "};
        Tokenizer* test = new Tokenizer("mkdir folder||echo #&&||;anythinggoes");
        EXPECT_EQ(test->returnArgs(), comment);
}


TEST (TokenizerParse, 3CommandsWithCommentAndQuotes) {
        std::vector<std::string> monster{"mkdir folder ","&&", " echo \"# && || ;\" ","||", " ls -a "};
	Tokenizer* test = new Tokenizer("mkdir folder && echo \"# && || ;\" || ls -a #comment");
        EXPECT_EQ(test->returnArgs(), monster);
}
#endif
