# learnCppSTLwithGTest
Learn C++ STL DataStrucures (Container), Design Patterns, MultiThread Applications with Google Test &amp; Mock

In this solution Modern C++ concepts as well as other important topics like Design Patterns are investigated with  Google test.
So it is helpful someone who want to learn these concepts. 
The project will be developed in VS 2017, then we switch to 2020. Community edition, which is free should be fine. 

People's brain always like to learn with examples. Instead of printing to console and keep inspecting the results on the console,
we will develop our learning skill by writing the google test.
So if the code snippet does not work as intented we see that test will fail.

As an example, let's assume that we want to learn the std::vector push_back method.
We first define the test case which is "TestStdVector", ant the specifi test name "PushBack".

The learning and testing curve will be as in the steps below.
   * Preparations
   * Operation
   * Tests

/*
Test: Add 3 elements to vector with push_back, then verify.
*/
TEST(TestStdVector, PushBack) {
  // Preparations
  std::vector<int> vector;
  
  // Operation
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);

  // Tests
  // Compare vector with different methods
  EXPECT_EQ(vector[0], 1);
  EXPECT_EQ(vector[1], 2);
  EXPECT_EQ(vector[2], 3);

  ASSERT_THAT(vector, ElementsAreArray(std::vector<int>{1, 2, 3}));
  ASSERT_THAT(vector, ElementsAre(1, 2, 3));
}
