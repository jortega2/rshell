#include "gtest/gtest.h"

#include "commented_command_tests.cpp"
#include "exit_command_tests.cpp"
#include "multiple_command_tests.cpp"
#include "single_command_tests.cpp"
#include "test_literal_tests.cpp"
#include "test_symbolic_tests.cpp"
#include "precedence_tests.cpp"

int main2(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
