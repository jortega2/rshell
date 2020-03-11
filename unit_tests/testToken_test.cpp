#ifndef __TESTTOKEN_TEST_HPP__
#define __TESTTOKEN_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/testToken.hpp"

//testing for parsing and exeucte function.
//Execute function returns 1 if path is valid and flag criteria is met. 
//Execute returns 0 otherwise.

TEST (testTokenParse, genericCommmand) {	
	TestToken* test = new TestToken("test -d path/to/file");
	EXPECT_EQ(test->getStrings("flag"), "-d");
	EXPECT_EQ(test->getStrings("file"), "path/to/file");
	EXPECT_EQ(test->stringify(), "test -d path/to/file");
}

TEST (testTokenParse, bracketsCommmand) {
        TestToken* test = new TestToken("[ -f path/to/file ]");
        EXPECT_EQ(test->getStrings("flag"), "-f");
        EXPECT_EQ(test->getStrings("file"), "path/to/file");
	EXPECT_EQ(test->stringify(), "[ -f path/to/file ]");
}

TEST (testTokenParse, whiteSpace) {
        TestToken* test = new TestToken("       test         -d         path/to/file       ");
        EXPECT_EQ(test->getStrings("flag"), "-d");
        EXPECT_EQ(test->getStrings("file"), "path/to/file");
	EXPECT_EQ(test->stringify(), "       test         -d         path/to/file       ");
}

TEST (testTokenParse, bracketWhiteSpace) {
        TestToken* test = new TestToken(" [            -e           path/to/file        ]");
        EXPECT_EQ(test->getStrings("flag"), "-e");
        EXPECT_EQ(test->getStrings("file"), "path/to/file");
	EXPECT_EQ(test->stringify(), " [            -e           path/to/file        ]");
}

TEST (testTokenCmds, directoryCommand) {
        TestToken* test = new TestToken("test -d src");
	EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(),"test -d src" );
}


TEST (testTokenCmds, missingDirectoryCommand) {
        TestToken* test = new TestToken("test -d path/to/file");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -d path/to/file");
}

TEST (testTokenCmds, invalidDirectoryCommand) {
        TestToken* test = new TestToken("test -d CMakeLists.txt");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -d CMakeLists.txt");
}

TEST (testTokenCmds, regularCommmand) {
        TestToken* test = new TestToken("test -f CMakeLists.txt");
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "test -f CMakeLists.txt");
}

TEST (testTokenCmds, invalidRegularCommmand) {
        TestToken* test = new TestToken("test -f src");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -f src");
}

TEST (testTokenCmds, missingRegularCommmand) {
        TestToken* test = new TestToken("test -f CMa.txt");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -f CMa.txt");
}

TEST (testTokenCmds, fileDirectoryCommmand) {
        TestToken* test = new TestToken("test -e CMakeLists.txt");
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "test -e CMakeLists.txt");
}

TEST (testTokenCmds, invalidFileDirectoryCommmand) {
        TestToken* test = new TestToken("test -e src");
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "test -e src");
}

TEST (testTokenCmds, missingFileDirectoryCommmand) {
        TestToken* test = new TestToken("test -e CMa.txt");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -e CMa.txt");
}

TEST (testTokenCmds, moFlagCommmand) {
        TestToken* test = new TestToken("test CMakeLists.txt");
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "test CMakeLists.txt");
}

TEST (testTokenCmds, invalidNoFlagCommmand) {
        TestToken* test = new TestToken("test src");
        EXPECT_EQ(test->execute(), 1);
	EXPECT_EQ(test->stringify(), "test src");
}

TEST (testTokenCmds, missingNoFlagCommmand) {
        TestToken* test = new TestToken("test CMa.txt");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(),"test CMa.txt" );
}

TEST (testTokenCmds, missingPath) {
        TestToken* test = new TestToken("test ");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test ");
}

TEST (testTokenCmds, InvalidFlag) {
        TestToken* test = new TestToken("test -z  CMa.txt");
        EXPECT_EQ(test->execute(), 0);
	EXPECT_EQ(test->stringify(), "test -z  CMa.txt");
}

#endif
