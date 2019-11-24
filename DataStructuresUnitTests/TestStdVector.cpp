#include "pch.h"

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
Inserts a new element at the end of the vector, right after its current last
element. This new element is constructed in place using args as the arguments
for its constructor.
*/
TEST(TestStdVector, EmplaceBack) {
  // Preparations
  std::vector<int> vector{1, 2, 3};

  // Operation
  vector.emplace_back(4);
  vector.emplace_back(5);

  // Tests
  ASSERT_THAT(vector, ElementsAre(1, 2, 3, 4, 5));
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

TEST(TestStdVector, Emplace) {
  /*
   The container is extended by inserting a new element at position.
   This new element is constructed in place using args as the arguments for its
   construction.
  */

  std::vector<int> vector = {1, 2, 3};

  // Operations && Tests
  auto it = vector.emplace(vector.begin(), 4);
  ASSERT_THAT(vector, ElementsAre(4, 1, 2, 3));
  EXPECT_EQ(*it, 4);

  vector.emplace(vector.end(), 5);
  ASSERT_THAT(vector, ElementsAre(4, 1, 2, 3, 5));
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

TEST(TestStdVector, Begin) {
  // Preparations
  std::vector<int> vector{1, 2};
  ASSERT_THAT(vector, ElementsAre(1, 2));

  // Operations&& Tests
  // it provides the iterator, so it needs to be dereferenced via *
  EXPECT_EQ(*vector.begin(), 1);
}

TEST(TestStdVector, Capacity) {
  /*
Returns the size of the storage space currently allocated for the vector,
expressed in terms of elements.
*/

  // Preparations
  std::vector<int> vector(100, 3);  // vector size 100, is filled with 3.

  // Operations&& Tests
  EXPECT_GE(vector.capacity(), vector.size());
}

TEST(TestStdVector, Clear) {
  // Preparations
  std::vector<int> vector{1, 2, 3};  // vector size 100, is filled with 3.
  ASSERT_THAT(vector, ElementsAre(1, 2, 3));

  // Operations
  vector.clear();

  // Tests
  ASSERT_THAT(vector, ElementsAre());

  // Operations
  vector.push_back(100);
  // Tests
  ASSERT_THAT(vector, ElementsAre(100));
}

TEST(TestStdVector, Data) {
  /*
    Returns a direct pointer to the memory
    array used internally by the vector to store its owned elements.
  */

  std::vector<int> vector(5);  // allocate vector with 5 elements.
  ASSERT_THAT(vector, ElementsAre(0, 0, 0, 0, 0));
  int* p = vector.data();

  // Operations: update element, then increase pointer and update values.

  *p = 10;  // vector[0] = 10
  EXPECT_EQ(vector[0], 10);

  ++p;
  *p = 20;
  EXPECT_EQ(vector[1], 20);
  p[2] = 100;
  EXPECT_EQ(vector[3], 100);

  // Tests
  ASSERT_THAT(vector, ElementsAre(10, 20, 0, 100, 0));
}
