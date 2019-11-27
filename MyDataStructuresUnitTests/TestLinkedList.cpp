#include "pch.h"

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

TEST(LinkedList, PushBack) {
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

TEST(TestStdlist, PushFront) {
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

TEST(TestStdlist, PopBack) {
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
