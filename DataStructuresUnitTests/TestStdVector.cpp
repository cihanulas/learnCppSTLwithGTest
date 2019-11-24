﻿#include "pch.h"

#include <vector>
#include "gmock\gmock.h"

using namespace testing;

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

/*
Test: Popback 3 elements to vector with push_back, then verify.
*/
TEST(TestStdVector, PopBack) {
  // Prepare input
  std::vector<int> vector{1, 2, 3, 4};

  // Check before the operation
  ASSERT_THAT(vector, ElementsAre(1, 2, 3, 4));

  // Operation
  vector.pop_back();
  vector.pop_back();

  // Check after the operation
  ASSERT_THAT(vector, ElementsAre(1, 2));

  // Operation pop all elements
  vector.pop_back();
  vector.pop_back();

  // Check with empty array
  ASSERT_THAT(vector, ElementsAre());
}

TEST(TestStdVector, Insert) {
  // Prepare input
  std::vector<int> vector{1, 2, 3, 4};

  // Check before the operation
  ASSERT_THAT(vector, ElementsAre(1, 2, 3, 4));

  // Operation => (O(n) - requires shifting operation if not inserted back)
  // insert element into and an index;
  size_t index = 0;  // insert front
  vector.insert(vector.begin() + index, 5);

  // Check after the operation
  ASSERT_THAT(vector, ElementsAre(5, 1, 2, 3, 4));

  // insert to second 2
  index = 2;
  vector.insert(vector.begin() + index, 6);
  ASSERT_THAT(vector, ElementsAre(5, 1, 6, 2, 3, 4));

  // insert to end
  vector.insert(vector.end(), 7);
  ASSERT_THAT(vector, ElementsAre(5, 1, 6, 2, 3, 4, 7));

  // insert a vector from another vector
  std::vector<int> source{100, 200, 300};
  vector.insert(vector.end(), source.begin(), source.end());
  ASSERT_THAT(vector, ElementsAre(5, 1, 6, 2, 3, 4, 7, 100, 200, 300));

  // insert from array to the beginning of the array
  int array[] = {501, 502, 503};
  vector.insert(vector.begin(), array, array + 3);
  ASSERT_THAT(vector,
              ElementsAre(501, 502, 503, 5, 1, 6, 2, 3, 4, 7, 100, 200, 300));
}

/*
Assigns new contents to the vector, replacing its current contents, and
modifying its size accordingly.
*/
TEST(TestStdVector, Assign) {
  // Prepare input
  std::vector<int> vector;
  vector.assign(4, 100);  // 4 ints with a value of 100
  ASSERT_THAT(vector, ElementsAre(100, 100, 100, 100));

  // assign from one vector element to another vector
  std::vector<int> new_vector{1, 2, 3, 4};  // elements will be cleared
  ASSERT_THAT(new_vector, ElementsAre(1, 2, 3, 4));
  new_vector.assign(vector.begin(), vector.end() - 2);
  ASSERT_THAT(new_vector, ElementsAre(100, 100));

  {
    int array[] = {1, 3, 5};
    std::vector<int> vector;
    vector.assign(array, array + 3);  // assigning from array.

    // Check with empty array
    ASSERT_THAT(vector, ElementsAre(1, 3, 5));
  }
}

TEST(TestStdVector, At) {
  std::vector<int> vector{1, 2};
  ASSERT_THAT(vector, ElementsAre(1, 2));

  EXPECT_EQ(vector[0], 1);
  EXPECT_EQ(vector[1], 2);

  EXPECT_EQ(vector.at(0), 1);
  EXPECT_EQ(vector.at(1), 2);

  // Reaching to field does not exist, vector[2] does not throw, use at()
  // instead.
  EXPECT_THROW(vector.at(2), std::out_of_range);
  // EXPECT_THROW(vector[2], std::out_of_range);
}

TEST(TestStdVector, Back) {
  // Preparations
  std::vector<int> vector{1, 2};
  ASSERT_THAT(vector, ElementsAre(1, 2));

  // Operations && Tests
  EXPECT_EQ(vector.back(), 2);
  vector.pop_back();
  EXPECT_EQ(vector.back(), 1);
}
