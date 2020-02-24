#include "gtest/gtest.h"

#include "Tokenizer_test.cpp"
#include "cmdToken_test.cpp"
#include "andToken_test.cpp"
#include "orToken_test.cpp"
#include "semiToken_test.cpp"
#include "Executor_test.cpp"
#include "testToken_test.cpp"

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
