#include "pch.h"

#include <list>
#include "gmock\gmock.h"

using namespace testing;

/*
Test: Add 3 elements to list with push_back, then verify.
*/
TEST(TestStdlist, PushBack) {
  /*
  O(1)
  */
  // Preparations
  std::list<int> list;

  // Operation
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Tests
  ASSERT_THAT(list, ElementsAre(1, 2, 3));
}

/*
Test: Add 3 elements to list with push_back, then verify.
*/
TEST(TestStdlist, PushFront) {
  /*
  O(1)
  */

  // Preparations
  std::list<int> list;

  // Operation
  list.push_front(1);
  list.push_back(2);

  // Tests
  ASSERT_THAT(list, ElementsAre(1, 2));
}

/*
Inserts a new element at the end of the list, right after its current last
element. This new element is constructed in place using args as the arguments
for its constructor.
*/
TEST(TestStdlist, EmplaceBack) {
  /*
  O(1)
  */

  // Preparations
  std::list<int> list{1, 2, 3};

  // Operation
  list.emplace_back(4);
  list.emplace_back(5);

  // Tests
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 4, 5));
}

TEST(TestStdlist, EmplaceFront) {
  /*
  O(1)
  */

  // Preparations
  std::list<int> list{1, 2, 3};

  // Operation
  list.emplace_front(4);
  list.emplace_front(5);

  // Tests
  ASSERT_THAT(list, ElementsAre(5, 4, 1, 2, 3));
}

/*
Test: Popback 3 elements to list with push_back, then verify.
*/
TEST(TestStdlist, PopBack) {
  // Prepare input
  std::list<int> list{1, 2, 3, 4};

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

/*
Test: Popback 3 elements to list with push_back, then verify.
*/
TEST(TestStdlist, PopFront) {
  // Prepare input
  std::list<int> list{1, 2, 3, 4};

  // Operation
  list.pop_front();

  // Check after the operation
  ASSERT_THAT(list, ElementsAre(2, 3, 4));
}

TEST(TestStdlist, Insert) {
  /*
  Linear in the number of elements inserted.
  O(m)
  */
  // Prepare input
  std::list<int> list{1, 2, 3, 4};

  // Check before the operation
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 4));

  // Operation => (O(n) - requires shifting operation if not inserted back)
  // insert element into and an index;
  size_t index = 0;  // insert front
  list.insert(std::next(list.begin(), index), 5);

  // Check after the operation
  ASSERT_THAT(list, ElementsAre(5, 1, 2, 3, 4));

  // insert to second 2
  index = 2;
  list.insert(std::next(list.begin(), index), 6);
  ASSERT_THAT(list, ElementsAre(5, 1, 6, 2, 3, 4));

  // insert to end
  list.insert(list.end(), 7);
  ASSERT_THAT(list, ElementsAre(5, 1, 6, 2, 3, 4, 7));

  // insert a list from another list
  std::list<int> source{100, 200, 300};
  list.insert(list.end(), source.begin(), source.end());
  ASSERT_THAT(list, ElementsAre(5, 1, 6, 2, 3, 4, 7, 100, 200, 300));

  // insert from array to the beginning of the array
  int array[] = {501, 502, 503};
  list.insert(list.begin(), array, array + 3);
  ASSERT_THAT(list,
              ElementsAre(501, 502, 503, 5, 1, 6, 2, 3, 4, 7, 100, 200, 300));
}

TEST(TestStdlist, Emplace) {
  /*
   The container is extended by inserting a new element at position.
   This new element is constructed in place using args as the arguments for its
   construction.
  */

  std::list<int> list = {1, 2, 3};

  // Operations && Tests
  auto it = list.emplace(list.begin(), 4);
  ASSERT_THAT(list, ElementsAre(4, 1, 2, 3));
  EXPECT_EQ(*it, 4);

  list.emplace(list.end(), 5);
  ASSERT_THAT(list, ElementsAre(4, 1, 2, 3, 5));
}

/*
Assigns new contents to the list, replacing its current contents, and
modifying its size accordingly.
*/
TEST(TestStdlist, Assign) {
  /*
  O(n)
  */
  // Prepare input
  std::list<int> list;
  list.assign(4, 100);  // 4 ints with a value of 100
  ASSERT_THAT(list, ElementsAre(100, 100, 100, 100));

  // assign from one list element to another list
  std::list<int> new_list{1, 2, 3, 4};  // elements will be cleared
  ASSERT_THAT(new_list, ElementsAre(1, 2, 3, 4));
  new_list.assign(list.begin(), std::prev(list.end(), 2));

  ASSERT_THAT(new_list, ElementsAre(100, 100));

  {
    int array[] = {1, 3, 5};
    std::list<int> list;
    list.assign(array, array + 3);  // assigning from array.

    // Check with empty array
    ASSERT_THAT(list, ElementsAre(1, 3, 5));
  }
}

TEST(TestStdlist, Back) {
  // Preparations
  std::list<int> list{1, 2};
  ASSERT_THAT(list, ElementsAre(1, 2));

  // Operations && Tests
  EXPECT_EQ(list.back(), 2);
  list.pop_back();
  EXPECT_EQ(list.back(), 1);
}

TEST(TestStdlist, Begin) {
  // Preparations
  std::list<int> list{1, 2};
  ASSERT_THAT(list, ElementsAre(1, 2));

  // Operations&& Tests
  // it provides the iterator, so it needs to be dereferenced via *
  EXPECT_EQ(*list.begin(), 1);
}

TEST(TestStdlist, Clear) {
  /*
  O(n)
  */
  // Preparations
  std::list<int> list{1, 2, 3};  // list size 100, is filled with 3.
  ASSERT_THAT(list, ElementsAre(1, 2, 3));

  // Operations
  list.clear();

  // Tests
  ASSERT_THAT(list, ElementsAre());

  // Operations
  list.push_back(100);
  // Tests
  ASSERT_THAT(list, ElementsAre(100));
}

TEST(TestStdlist, Empty) {
  /*
  O(1)
  */
  std::list<int> list;  // allocate list with 5 elements.

  EXPECT_TRUE(list.empty());
  list.push_back(1);  // allocate list with 5 elements.
  EXPECT_FALSE(list.empty());
}

TEST(TestStdlist, Erase) {
  /*
 Removes from the list either a single element (position) or a range of
 elements ([first,last)).

 Unlike other standard sequence containers (vectors), list and forward_list
 objects are specifically designed to be efficient inserting and removing
 elements in any position, even in the middle of the sequence.

 O(n):
 We go the element (n), then remove the item O(1)

 */
  std::list<int> list{1, 2, 3, 4, 5};  // allocate list with 5 elements.

  // Operation => O(n)
  auto it =
      list.erase(std::next(list.begin(), 1));  // remove element at index 2;
  ASSERT_THAT(list, ElementsAre(1, 3, 4, 5));
  EXPECT_EQ(*it, 3);
  // Remove last two elements
  list.erase(std::prev(list.end(), 2), list.end());
  ASSERT_THAT(list, ElementsAre(1, 3));
}

/*
A reference to the first element in the list container.
O(1)
*/
TEST(TestStdlist, Front) {
  std::list<int> list{1, 2, 3};

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.front(), *list.begin());
}

TEST(TestStdlist, MaxSize) {
  /*
  Returns the maximum number of elements that the list can hold.
  It is not guaranteed.
  */

  // Preparations
  std::list<int> list;
  for (int i = 0; i < 10; i++) list.push_back(i);
  auto max_size = list.max_size();
  EXPECT_GT(max_size, 1e9);  // 1e9 integer
}

TEST(TestStdlist, AssignmentOperator) {
  /*
  Assigns new contents to the container,
  replacing its current contents, and modifying its size accordingly.
  */
  std::list<int> foo{1, 2, 3};
  ASSERT_THAT(foo, ElementsAre(1, 2, 3));

  std::list<int> bar{4, 5, 6};
  ASSERT_THAT(bar, ElementsAre(4, 5, 6));

  foo = bar;
  ASSERT_THAT(foo, ElementsAre(4, 5, 6));
  ASSERT_THAT(foo, bar);
}

TEST(TestStdlist, Resize) {
  /*
  Resizes the container so that it contains n elements.
  If n is smaller than the current container size, the content is reduced to its
  first n elements, removing those beyond (and destroying them).

  If n is greater than the current container size, the content is expanded by
  inserting at the end as many elements as needed to reach a size of n. If val
  is specified, the new elements are initialized as copies of val, otherwise,
  they are value-initialized.
  */

  std::list<int> list{1, 2, 3, 4, 5, 6};
  list.resize(3);
  ASSERT_THAT(list, ElementsAre(1, 2, 3));

  list.resize(6, 100);  // value specifed, 100s will be inserted
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 100, 100, 100));

  list.resize(7);  // value not specified, so 0 will be inserted
  ASSERT_THAT(list, ElementsAre(1, 2, 3, 100, 100, 100, 0));
}

TEST(TestStdlist, Size) {
  /*
  Returns the number of elements in the list.
  */
  std::list<int> list{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(list.size(), 6);
  list.resize(3);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestStdlist, Swap) {
  /*
  Returns the number of elements in the list.
  */
  std::list<int> foo{1, 2, 3};
  std::list<int> bar{4, 5, 6};
  ASSERT_THAT(foo, ElementsAre(1, 2, 3));
  ASSERT_THAT(bar, ElementsAre(4, 5, 6));

  // Operation
  foo.swap(bar);

  // Test
  ASSERT_THAT(foo, ElementsAre(4, 5, 6));
  ASSERT_THAT(bar, ElementsAre(1, 2, 3));

  std::swap(foo, bar);
  ASSERT_THAT(foo, ElementsAre(1, 2, 3));
  ASSERT_THAT(bar, ElementsAre(4, 5, 6));
}

TEST(TestStdlist, Compare) {
  /*
  Returns the number of elements in the list.
  */
  std::list<int> foo{1, 2, 3};
  std::list<int> bar{4, 5, 6};

  EXPECT_TRUE(foo != bar);
  foo = bar;
  EXPECT_TRUE(foo == bar);
}

TEST(TestStdlist, Remove) {
  /*
  O(n)
  remove by value
  */
  std::list<int> list{1, 200, 3, 200};
  list.remove(200);
  ASSERT_THAT(list, ElementsAre(1, 3));
}

TEST(TestStdlist, RemoveIF) {
  /*remove by value*/
  auto values_greater_than_100 = [](auto value) { return value > 100; };

  struct values_less_than_50 {
    bool operator()(const int& value) { return value < 50; }
  };

  std::list<int> list{10, 11, 12, 13, 98, 102};
  list.remove_if([](auto value) { return value % 2; });  // remove odd one
  ASSERT_THAT(list, ElementsAre(10, 12, 98, 102));

  list.remove_if(values_greater_than_100);  // remove odd one

  ASSERT_THAT(list, ElementsAre(10, 12, 98));
  list.remove_if(values_less_than_50());  // remove odd one
  ASSERT_THAT(list, ElementsAre(98));
}

TEST(TestStdlist, Sort) {
  std::list<int> first{2, 7, 4};

  // Preparations
  first.sort();

  // Test
  ASSERT_THAT(first, ElementsAre(2, 4, 7));

  first.sort(std::greater<int>());
  ASSERT_THAT(first, ElementsAre(7, 4, 2));
}

TEST(TestStdlist, Merge) {
  std::list<double> first{3.1, 2.2, 2.9};
  std::list<double> second{3.7, 7.1, 1.4};

  // Preparations
  first.sort();
  second.sort();

  ASSERT_THAT(first, ElementsAre(2.2, 2.9, 3.1));
  ASSERT_THAT(second, ElementsAre(1.4, 3.7, 7.1));

  // Opertaions
  first.merge(second);
  // (second is now empty)

  // Tests
  EXPECT_TRUE(second.empty());
  ASSERT_THAT(first, ElementsAre(1.4, 2.2, 2.9, 3.1, 3.7, 7.1));

  second.push_back(2.1);
  second.push_back(7);

  first.merge(second, [](auto value1, auto value2) {
    return int(value1) < int(value2);  // compare only integer part
  });

  // Tests
  EXPECT_TRUE(second.empty());
  ASSERT_THAT(first, ElementsAre(1.4, 2.2, 2.9, 2.1, 3.1, 3.7, 7.1, 7));
}

TEST(TestStdlist, Reverse) {
  std::list<double> list{1, 2, 3};

  list.reverse();

  ASSERT_THAT(list, ElementsAre(3, 2, 1));
}

TEST(TestStdlist, Splice) {
  /*Transfer elements
  entire list  (1)  void splice (iterator position, list& x);
single element (2)  void splice (iterator position, list& x, iterator i);
element range  (3)  void splice (iterator position, list& x, iterator first,
iterator last);

 The first version (1) transfers all the elements of x into the container.
The second version (2) transfers only the element pointed by i from x into the
container.
The third version (3) transfers the range [first,last) from x into
the container.

  */

  std::list<int> list1{1, 2, 3};
  std::list<int> list2{4, 5, 6};

  // list1.splice(list1.begin(), list2.begin(), std::next(list2.begin()));
  // Test 1
  list1.splice(list1.begin(), list2);  // move entire list
  ASSERT_THAT(list1, ElementsAre(4, 5, 6, 1, 2, 3));
  ASSERT_THAT(list2, ElementsAre());

  // Prepare
  list1.assign({1, 2, 3});
  list2.assign({4, 5, 6});

  // Test 2: Transfer only the 0th element (4) of list2 to after list1 next
  list1.splice(++list1.begin(), list2, list2.begin());
  ASSERT_THAT(list1, ElementsAre(1, 4, 2, 3));
  ASSERT_THAT(list2, ElementsAre(5, 6));

  // Prepare
  list1.assign({1, 2, 3, 4});
  list2.assign({5, 6, 7, 8});

  // Test 3: Transfer 1 and 2 elements (5,6) of list2 begin.
  auto it_start = std::next(list2.begin(), 1);
  auto it_stop = std::next(list2.begin(), 3);  // 3 element is not included.

  list1.splice(list1.begin(), list2, it_start, it_stop);
  ASSERT_THAT(list1, ElementsAre(6, 7, 1, 2, 3, 4));
  ASSERT_THAT(list2, ElementsAre(5, 8));
}

TEST(TestStdlist, Unique) {
  std::list<double> list{1, 2.2, 3, 2.2};

  // must be sorted beforehand.
  list.sort();
  list.unique();

  ASSERT_THAT(list, ElementsAre(1, 2.2, 3));
}
