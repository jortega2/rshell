#ifndef __TOKENIZER_TEST_HPP__
#define __TOKENIZER_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Tokenizer.hpp"

TEST (TokenizerTest, OneCommand) {
	std::vector<std::string> one {"ls -a"};
	Tokenizer* test = new Tokenizer("ls -a");
	EXPECT_EQ(test->returnArgs(), one);
}

TEST (TokenizerTest, TwoCommands) {
	std::vector<std::string> two {"mkdir folder", "ls -a"};
        Tokenizer* test = new Tokenizer("mkdir folder;ls -a");
        EXPECT_EQ(test->returnArgs(), two);
}

TEST (TokenizerTest, ThreeCommands) {
	std::vector<std::string> three {"mkdir folder", " ls -a "," echo here"};
        Tokenizer* test = new Tokenizer("mkdir folder|| ls -a && echo here");
        EXPECT_EQ(test->returnArgs(), three);
}

TEST (TokenizerTest, FourCommands) {
        std::vector<std::string> four {"   mkdir folder ", " ls -a "," echo here ", " ls"};
	Tokenizer* test = new Tokenizer("   mkdir folder ; ls -a || echo here && ls");
        EXPECT_EQ(test->returnArgs(), four);
}

TEST (TokenizerTest, QuoteCommands) {
        std::vector<std::string> quotes{"mkdir folder", "echo \"&& || ;\""};
	Tokenizer* test = new Tokenizer("mkdir folder&&echo \"&& || ;\"");
        EXPECT_EQ(test->returnArgs(), quotes);
}

TEST (TokenizerTest, CommentCommands) {
	std::vector<std::string> comment{"mkdir folder", "echo "};
        Tokenizer* test = new Tokenizer("mkdir folder||echo #&&||;anythinggoes");
        EXPECT_EQ(test->returnArgs(), comment);
}


TEST (TokenizerTest, 3CommandsWithCommentAndQuotes) {
        std::vector<std::string> monster{"mkdir folder ", " echo \"# && || ;\" ", " ls -a "};
	Tokenizer* test = new Tokenizer("mkdir folder && echo \"# && || ;\" || ls -a #comment");
        EXPECT_EQ(test->returnArgs(), monster);
}
#endif
