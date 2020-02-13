#ifndef __EXECUTOR_TEST_HPP__
#define __EXECUTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Executor.hpp"

TEST (ExecutorIsValid, 2Args1Connector) {
	std::vector<std::string> args {"ls -a", "echo pog"};
	std::vector<std::string> conns {"||"};
	Executor* test = new Executor(args, conns);
	EXPECT_EQ(test->isValid(), 1);
}

TEST (ExecutorIsValid, 5Args4Connector) {
        std::vector<std::string> args {"ls -a", "echo hello", "mkdir test", "echo world", "git status"};
        std::vector<std::string> conns {";", "&&", "||", ";"};
        Executor* test = new Executor(args, conns);
        EXPECT_EQ(test->isValid(), 1);
}

TEST (ExecutorIsValid, 3Args4Connector) {
        std::vector<std::string> args {"ls -a", "echo hello", "mkdir test"};
        std::vector<std::string> conns {";", "&&", "||", ";"};
        Executor* test = new Executor(args, conns);
        EXPECT_EQ(test->isValid(), 0);
}

TEST (ExecutorIsValid, 5Argse5Connector) {
	std::vector<std::string> args {"ls -a", "echo hello", "mkdir test", "echo world", "git status"};
        std::vector<std::string> conns {";", "&&", "||", ";", "&&"};
        Executor* test = new Executor(args, conns);
        EXPECT_EQ(test->isValid(), 0);
}

TEST (ExecutorIsValid, 3Args1Connector) {
	//note: the logic is flawed, you can't have three execs/args and only 1 connector.
	//if this happens, then the tokenizer parsing failed to do its job properly. 
	//This kind of error is outside the scope of Executor.
	//Nevertheless, if this edge case happends the executor will read it as valid.
        std::vector<std::string> args {"ls -a", "echo pog", "mkdir test"};
        std::vector<std::string> conns {"||"};
        Executor* test = new Executor(args, conns);
        EXPECT_EQ(test->isValid(), 1);
}



#endif

