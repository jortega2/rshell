#include "gtest/gtest.h"

#include "Tokenizer_test.hpp"
#include "cmdToken_test.hpp"
#include "andToken_test.hpp"
#include "Executor_test.hpp"

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
