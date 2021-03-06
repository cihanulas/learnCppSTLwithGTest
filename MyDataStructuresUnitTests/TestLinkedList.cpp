﻿#include "pch.h"

#include "LinkedList.h"
#include "gmock\gmock.h"

/*
Here our aim is to use exaclty the same test methods as in TestStdList.

*/

MATCHER(IsEven, "") { return (arg % 2) == 0; }

// Matcher for LinkedList, similar to existing ElemntsAre
MATCHER(ElementsAre, "") {
  auto list = static_cast<LinkedList>(arg);
  return list.empty();
}

// Matcher for LinkedList, similar to existing ElemntsAre
MATCHER_P(ElementsAre, p0, "") {
  auto list = static_cast<LinkedList>(arg);
  return p0 == list.at(0);
}

// Matcher for LinkedList, similar to existing ElemntsAre
MATCHER_P2(ElementsAre, p0, p1, "") {
  auto list = static_cast<LinkedList>(arg);
  auto a = list.empty();
  bool res = p0 == list.at(0) && p1 == list.at(1);
  return res;
}

// Matcher for LinkedList, similar to existing ElemntsAre
MATCHER_P3(ElementsAre, p0, p1, p2, "") {
  auto list = static_cast<LinkedList>(arg);
  auto a = list.empty();
  bool res = p0 == list.at(0) && p1 == list.at(1) && p2 == list.at(2);
  return res;
}

MATCHER_P4(ElementsAre, p0, p1, p2, p3, "") {
  auto list = static_cast<LinkedList>(arg);
  auto a = list.empty();
  bool res = p0 == list.at(0) && p1 == list.at(1) && p2 == list.at(2) &&
             p3 == list.at(3);
  return res;
}

// Matcher for LinkedList, similar to existing ElemntsAre
MATCHER_P5(ElementsAre, p0, p1, p2, p3, p4, "") {
  auto list = static_cast<LinkedList>(arg);
  auto a = list.empty();
  bool res = p0 == list.at(0) && p1 == list.at(1) && p2 == list.at(2) &&
             p3 == list.at(3) && p4 == list.at(4);
  // int value = *list.node_at(0);
  return res;
}

TEST(TestLinkedList, PushBack) {
  /*
  O(1):
  */
  // Preparations
  LinkedList list;

  // Operation
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  // Tests
  // ASSERT_THAT(list, ElementsAre(1, 2, 3));
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 4, 5));
}

TEST(TestLinkedList, PushFront) {
  /*
  O(1)
  */

  // Preparations
  LinkedList list;

  // Operation
  list.push_front(1);
  list.push_front(2);

  // Tests
  ASSERT_THAT(list, ElementsAre(2, 1));
}

TEST(TestLinkedList, PopBack) {
  // Prepare input
  LinkedList list{1, 2, 3, 4};

  // Check before the operation
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 4));

  // Operation
  list.pop_back();
  list.pop_back();

  // Check after the operation
  ASSERT_THAT(list, ElementsAre(1, 2));

  // Operation pop all elements
  list.pop_back();
  list.pop_back();

  // Check with empty array
  ASSERT_THAT(list, ElementsAre());
}

TEST(TestLinkedList, PopFront) {
  // Prepare input
  LinkedList list{1, 2, 3, 4};

  // Operation
  list.pop_front();

  // Check after the operation
  ASSERT_THAT(list, ElementsAre(2, 3, 4));
}
TEST(TestLinkedList, Next) {
  LinkedList list{1, 2};
  auto begin = list.begin();
  auto next = std::next(begin);
  auto val = *next;
  EXPECT_EQ(next->value, 2);
}

TEST(TestLinkedList, Insert) {
  /*
  Linear in the number of elements inserted.
  O(m)
  */
  // Prepare input
  LinkedList list{1, 2};

  // Check before the operation
  ASSERT_THAT(list, ElementsAre(1, 2));

  // insert element into index 1
  list.insert(1, 5);
  // Check after the operation
  ASSERT_THAT(list, ElementsAre(1, 5, 2));
}

TEST(TestLinkedList, Erase) {
  LinkedList list{10, 20, 30};

  list.erase(1);  // by index
  ASSERT_THAT(list, ElementsAre(10, 30));
}

TEST(TestLinkedList, Remove) {
  LinkedList list{10, 20, 30};

  list.remove(20);  // by index
  ASSERT_THAT(list, ElementsAre(10, 30));
}
