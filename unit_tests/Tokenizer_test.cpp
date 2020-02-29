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
	test->parse();
	EXPECT_EQ(test->returnArgs(), one);
}

TEST (TokenizerParse, TwoCommands) {
	std::vector<std::string> two {"mkdir folder",";","ls -a"};
        Tokenizer* test = new Tokenizer("mkdir folder;ls -a");
	test->parse();
        EXPECT_EQ(test->returnArgs(), two);
}

TEST (TokenizerParse, ThreeCommands) {
	std::vector<std::string> three {"mkdir folder", "||", "ls -a", "&&", "echo here"};
        Tokenizer* test = new Tokenizer("mkdir folder|| ls -a && echo here");
	test->parse();
        EXPECT_EQ(test->returnArgs(), three);
}

TEST (TokenizerParse, FourCommands) {
        std::vector<std::string> four {"mkdir folder", ";", "ls -a", "||", "echo here","&&","ls"};
	Tokenizer* test = new Tokenizer("   mkdir folder ; ls -a || echo here && ls");
	test->parse();
        EXPECT_EQ(test->returnArgs(), four);
}

TEST (TokenizerParse, QuoteCommands) {
        std::vector<std::string> quotes{"mkdir folder","&&", "echo \"&& || ;\""};
	Tokenizer* test = new Tokenizer("mkdir folder&&echo \"&& || ;\"");
	test->parse();
        EXPECT_EQ(test->returnArgs(), quotes);
}

TEST (TokenizerParse, CommentCommands) {
	std::vector<std::string> comment{"mkdir folder","||", "echo"};
        Tokenizer* test = new Tokenizer("mkdir folder||echo #&&||;anythinggoes");
	test->parse();
        EXPECT_EQ(test->returnArgs(), comment);
}


TEST (TokenizerParse, 3CommandsWithCommentAndQuotes) {
        std::vector<std::string> monster{"mkdir folder","&&", "echo \"# && || ;\"","||", "ls -a"};
	Tokenizer* test = new Tokenizer("mkdir folder && echo \"# && || ;\" || ls -a #comment");
	test->parse();
        EXPECT_EQ(test->returnArgs(), monster);
}

TEST (TokenizerShuntingYard, NormalCommandNoParen) {
        std::vector<std::string> monster{"||","&&","mkdir folder","echo \"# && || ;\"", "ls -a"};
        Tokenizer* test = new Tokenizer("mkdir folder && echo \"# && || ;\" || ls -a #comment");
        test->parse();
	test->shuntingYardAlgorithm();
        EXPECT_EQ(test->returnArgs(), monster);
}
TEST (TokenizerShuntingYard, VideoCommand) {
        std::vector<std::string> vid{"||","&&","echo A", "echo B", "&&", "echo C", "echo D"};
        Tokenizer* test = new Tokenizer("( echo A && echo B ) || ( echo C && echo D )");
        test->parse();
        test->shuntingYardAlgorithm();
        EXPECT_EQ(test->returnArgs(), vid);
}

TEST (TokenizerShuntingYard, NormalMixedWithParenCommand) {
        std::vector<std::string> cmd{"&&", "&&", ";", "echo A", "echo B","||", "echo C", "echo D", "echo E"};
        Tokenizer* test = new Tokenizer("echo A ; echo B && ( echo C || echo D ) && echo E");
        test->parse();
        test->shuntingYardAlgorithm();
        EXPECT_EQ(test->returnArgs(), cmd);
}

TEST (TokenizerShuntingYard, NestedParenthesis) {
        std::vector<std::string> cmd{";","&&", "||", ";", "echo A", "echo B", "&&", "echo C", "echo D", "echo E", "echo F" };
        Tokenizer* test = new Tokenizer("((echo A ; echo B) || ( echo C && echo D) && (echo E)) ; (echo F)");
        test->parse();
        test->shuntingYardAlgorithm();
        EXPECT_EQ(test->returnArgs(), cmd);
}

TEST (TokenizerShuntingYard, NestedParenthesis2) {
        std::vector<std::string> cmd{"echo A"};
        Tokenizer* test = new Tokenizer("(((((((echo A)))))");
        test->parse();
        test->shuntingYardAlgorithm();
        EXPECT_EQ(test->returnArgs(), cmd);
}
#endif
