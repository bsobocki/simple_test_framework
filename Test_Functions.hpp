#include "TestExceptions.hpp"
#include <functional>
#include <iostream>

namespace std
{
   string to_string(const char * str)
   {
      return string(str);
   }

   string to_string(const string & str)
   {
      return string(str);
   }
}

void __do_test__(const std::string testName, std::function<void()> testBody)
{
   #define colored(str, color) set ## color + str + endColor

   std::string message;
   std::string setGreen = "\033[32m";
   std::string setRed = "\033[31m";
   std::string endColor = "\033[m";

   std::string result = colored("passed", Green);

   try
   {
      testBody();
   }
   catch(const std::exception & e)
   {
      result = colored("failed", Red);
      message = "\n" + std::string(e.what());
   }

   std::cout << "[ " << result << " ]  Test: " << testName;
   std::cout << message << std::endl;
}

std::string assertFailDescription(const std::string assert_name, const std::string act_name, const std::string act_val, const std::string exp_name, const std::string exp_val)
{
   std::string exp = ( exp_name.empty() ? "" : "', '" + exp_name);

   return "  Check " + assert_name + ": '" + act_name + exp + "'\n" +
          "    actual: " + act_val + "\n" +
          "    expected: " + exp_val;
}

template<typename T>
void __AssertNeq__(const T & act_val, const T & exp_val, const char* act_name, const char * exp_name)
{
   if (act_val == exp_val) 
      throw NotEqualException(assertFailDescription("Not Equal", act_name, std::to_string(act_val), exp_name, std::to_string(exp_val)));
}

template<typename T>
void __AssertEq__(const T & act_val, const T & exp_val, const char* act_name, const char * exp_name)
{
   if (act_val != exp_val) 
      throw NotEqualException(assertFailDescription("Equal", act_name, std::to_string(act_val), exp_name, std::to_string(exp_val)));
}

void __AssertTrue__(const bool pred, const char* name)
{
   if (not pred)
      throw NotEqualException(assertFailDescription("True", name, "false", "", "true"));
}

void __AssertFalse__(const bool pred, const char* name)
{
   if (pred)
      throw NotEqualException(assertFailDescription("False", name, "true", "", "false"));
}