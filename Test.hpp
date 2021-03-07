#pragma once

#include "Test_Functions.hpp"
#include <vector>

#define LAMBDA_WITHOUT_BODY []()

struct __test__
{
   std::string name;
   std::function<void()> body;
};

#define ASSERT_EQ(actual, expect) __AssertEq__<decltype(expect)>(actual, expect, #actual, #expect)
#define ASSERT_NEQ(actual, expect) __AssertNeq__<decltype(expect)>(actual, expect, #actual, #expect)
#define ASSERT_TRUE(actual) __AssertTrue__(actual, #actual)
#define ASSERT_FALSE(actual) __AssertFalse__(actual, #actual)

#define RUN_TESTS \
   for (auto & test : tests) \
      __do_test__(test->name, test->body); \
      } // end of main()

#define TEST(test_name) \
   __test__ test_name {#test_name, nullptr}; \
   tests.push_back(&test_name); \
   test_name.body = LAMBDA_WITHOUT_BODY

#define INIT_TEST_FRAMEWORK int main() { std::vector<__test__*> tests;