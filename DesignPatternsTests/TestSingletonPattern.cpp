#include "pch.h"

#include "SingletonPattern.h"

TEST(TestSingletonPattern, GetInstance) {
  Singleton& pSingle1 = Singleton::getInstance();
  Singleton& pSingle2 = Singleton::getInstance();

  // compare pointers
  EXPECT_EQ(&pSingle1, &pSingle1);
}

// Test Looger is ThreadSafe Singleton
TEST(TestSingletonPattern, TestLogger) {
  auto& logger1 = Logger::getLogger();
  auto& logger2 = Logger::getLogger();

  // compare pointers
  EXPECT_EQ(&logger1, &logger2);

  // str = log(str) returns what it prints
  EXPECT_EQ(logger1.log("test"), "test");
}
