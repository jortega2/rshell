#ifndef __EXECUTOR_TEST_CPP__
#define __EXECUTOR_TEST_CPP__

#include "gtest/gtest.h"
#include "../header/Executor.hpp"

//note: Executors createTokens function is not tested because it is a void function. Changing it to return the tokens would change the structure of the program.
//See the integration tests for proper createTokens testing, as execute will not work if it fails.
//Executors execute function is not tested either, because the way the function is setup it would just be another set of integration tests. Check integration command tests for execute testing.


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
#endif

