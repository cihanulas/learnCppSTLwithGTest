#include "pch.h"

#include <set>
#include "gmock\gmock.h"

using namespace testing;

/* Set
 * Set is always in sorted order and element are unique
 * Self-balancing tree BST
 * Search time (with traversal) (log(n)), use find method.
 * Insertion time: log(n) + Rebalance
 * Deletion time: log(n) + Rebalance
 * Since it is already sorted, we can use functionss like binary_search(),
   lower_bound()
 */
TEST(TestStdset, Insert) {
  /*
    Extends the container by inserting new elements, effectively increasing the
    container size by the number of elements inserted.
     * Elements are always unique and kept in sorted order
     * So the insertion operation checks whether each inserted element is
      equivalent to an element already in the container, and if so, the
      element is not inserted, returning an iterator to this existing element
      (if the function returns a value)
  */

  // Prepare input
  std::set<int> set{1, 3, 4, 0, 2};

  // Test if in order
  ASSERT_THAT(set, ElementsAre(0, 1, 2, 3, 4));

  // Insert a non existing element
  set.insert(5);
  ASSERT_THAT(set, ElementsAre(0, 1, 2, 3, 4, 5));

  // Insert a non existing element
  auto res = set.insert(2);
  ASSERT_THAT(set, ElementsAre(0, 1, 2, 3, 4, 5));
  EXPECT_FALSE(res.second);  // not inserted
  EXPECT_EQ(*res.first, 2);  // iterator refering to 2
}

TEST(TestStdset, Emplace) {
  /*
     Similar to insert but this new element is constructed in place using
     args as the arguments for its construction.

     The element is constructed in-place by calling
     allocator_traits::construct with args forwarded.

     A similar member function exists, insert, which either copies or moves
     existing objects into the container.
  */
  std::set<int> set{1, 3, 4, 0, 2};
  auto it = set.emplace(5);
  ASSERT_THAT(set, ElementsAre(0, 1, 2, 3, 4, 5));
  EXPECT_EQ(*it.first, 5);
  // Operations && Tests
  // Pairs are also in order
  std::set<std::pair<int, int>> pair_set;
  pair_set.emplace(1, 1);  // or pair_set.insert({1, 1});
  pair_set.emplace(2, 1);
  pair_set.emplace(1, 2);
  pair_set.emplace(2, 2);
  pair_set.emplace(3, 2);
  pair_set.emplace(3, 3);
  pair_set.emplace(3, 1);

  ASSERT_THAT(pair_set,
              ElementsAre(Pair(1, 1), Pair(1, 2), Pair(2, 1), Pair(2, 2),
                          Pair(3, 1), Pair(3, 2), Pair(3, 3)));
}

TEST(TestStdset, EmplaceHint) {
  /*
    Similar to emplace but we provide hint to improve insertion perfance.
    If hint is not valuable then not meaningful.
  */

  std::set<int> set = {1, 2, 3};

  // Operations && Tests
  // No performace improvement.
  auto it = set.emplace_hint(set.begin(), 4);
  ASSERT_THAT(set, ElementsAre(1, 2, 3, 4));
  EXPECT_EQ(*it, 4);

  // Improves performace.
  it = set.emplace_hint(it, 5);
  ASSERT_THAT(set, ElementsAre(1, 2, 3, 4, 5));
  EXPECT_EQ(*it, 5);
}

TEST(TestStdset, Begin) {
  // Preparations
  std::set<int> set{1, 2};
  ASSERT_THAT(set, ElementsAre(1, 2));

  // Operations&& Tests
  // it provides the iterator, so it needs to be dereferenced via *
  EXPECT_EQ(*set.begin(), 1);
}

TEST(TestStdset, Clear) {
  // Preparations
  std::set<int> set{1, 2, 3};  // set size 100, is filled with 3.
  ASSERT_THAT(set, ElementsAre(1, 2, 3));

  // Operations
  set.clear();

  // Tests
  ASSERT_THAT(set, ElementsAre());

  // Operations
  set.insert(100);
  // Tests
  ASSERT_THAT(set, ElementsAre(100));
}

TEST(TestStdset, Empty) {
  std::set<int> set;  // allocate set with 5 elements.

  EXPECT_TRUE(set.empty());
  set.insert(1);  // allocate set with 5 elements.
  EXPECT_FALSE(set.empty());
}

TEST(TestStdset, Erase) {
  /*
     Removes from the set either a single element or a range of elements
     ([first,last)).
     This effectively reduces the container size by the number of elements
     removed, which are destroyed.

     Time complexity:
        For the first version (erase(position)), amortized constant.
        For the second version (erase(val)), logarithmic in container size.
        For the last version (erase(first,last)), linear in the distance between
        first and last.
 */
  std::set<int> set{1, 2, 3, 4, 5};  // allocate set with 5 elements.

  // Operation
  auto it =
      set.erase(std::next(set.begin(), 1));  // remove element (2) at index 1;
  ASSERT_THAT(set, ElementsAre(1, 3, 4, 5));
  EXPECT_EQ(*it, 3);
  // Remove last two elements
  set.erase(std::prev(set.end(), 2), set.end());
  ASSERT_THAT(set, ElementsAre(1, 3));

  // Remove element by value
  set.erase(3);
  ASSERT_THAT(set, ElementsAre(1));

  // Remove elements upto a value (not included)
  std::set<int> set2{1, 2, 10, 4, 5, 9};
  ASSERT_THAT(set2, ElementsAre(1, 2, 4, 5, 9, 10));
  set2.erase(set2.begin(), set2.find(5));  // 5 is not removed.
  ASSERT_THAT(set2, ElementsAre(5, 9, 10));
}

TEST(TestStdset, Count) {
  /*
    Searches the container for elements equivalent to val and
    returns 1 if found, else 0;
  */
  std::set<int> set{1, 2, 3, 4};
  EXPECT_EQ(set.count(1), 1);  // found
  EXPECT_EQ(set.count(5), 0);  // found
}

TEST(TestStdset, AssignmentOperator) {
  /*
    Assigns new contents to the container,
    replacing its current contents, and modifying its size accordingly.
  */
  std::set<int> foo{1, 2, 3};
  ASSERT_THAT(foo, ElementsAre(1, 2, 3));

  std::set<int> bar{4, 5, 6};
  ASSERT_THAT(bar, ElementsAre(4, 5, 6));

  foo = bar;
  ASSERT_THAT(foo, ElementsAre(4, 5, 6));
  ASSERT_THAT(foo, bar);
}

TEST(TestStdset, Size) {
  /*
    Returns the number of elements in the set.
  */
  std::set<int> set{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(set.size(), 6);
}

TEST(TestStdset, Swap) {
  /*
    Returns the number of elements in the set.
  */
  std::set<int> foo{1, 2, 3};
  std::set<int> bar{4, 5, 6};
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

TEST(TestStdset, Compare) {
  /*
    Returns the number of elements in the set.
  */
  std::set<int> foo{1, 2, 3};
  std::set<int> bar{4, 5, 6};

  // EXPECT_TRUE(foo != bar);
  foo = bar;
  // EXPECT_TRUE(foo == bar);
}

TEST(TestStdset, EqualRange) {
  /*
  Returns the bounds of a range that includes all the elements in the
  container that are equivalent to val.

  Because all elements in a set container are unique, the range returned will
  contain a single element at most.

  If no matches are found, the range returned has a length of zero, with both
  iterators pointing to the first element that is considered to go after val
  according to the container's internal comparison object (key_comp).
  Two elements of a set are considered equivalent if the container's comparison
  object returns false reflexively (i.e., no matter the order in which the
  elements are passed as arguments).
  */

  std::set<int> myset{10, 20, 30, 40, 50};

  auto ret = myset.equal_range(30);
  EXPECT_EQ(*ret.first, 30);   // lower_bound;
  EXPECT_EQ(*ret.second, 40);  // upper_bound;

  // if value not found
  ret = myset.equal_range(60);
  EXPECT_EQ(ret.first, myset.end());   // lower_bound;
  EXPECT_EQ(ret.second, myset.end());  // upper_bound;

  ret = myset.equal_range(11);
  EXPECT_EQ(*ret.first, 20);   // lower_bound;
  EXPECT_EQ(*ret.second, 20);  // upper_bound;
}

TEST(TestStdset, Find) {
  /*
    Searches the container for a value and returns an
    iterator to it if found, otherwise it returns an iterator to end().
  */
  std::set<int> set{10, 20, 30, 40, 50};
  auto it = set.find(10);
  // found
  EXPECT_EQ(*it, 10);
  EXPECT_NE(it, set.end());

  // not found
  auto it_2 = set.find(15);
  EXPECT_EQ(it_2, set.end());
}

TEST(TestStdset, KeyCompare) {
  /*
    Returns a copy of the comparison object used by the container.
    By default, this is a less object, which returns the same as operator<.
  */

  std::set<int> set{1, 2, 3, 4, 5};
  std::set<int> lt_3;
  std::set<int> ge_3;

  auto key_comp = set.key_comp();

  for (auto val : set) {
    if (key_comp(val, 3))
      lt_3.insert(val);
    else
      ge_3.insert(val);
  }
  ASSERT_THAT(lt_3, ElementsAre(1, 2));
  ASSERT_THAT(ge_3, ElementsAre(3, 4, 5));
}

TEST(TestStdset, ValueCompare) {
  /*
    ValueCompare==KeyComapare
    Returns a copy of the comparison object used by the container.
    By default, this is a less object, which returns the same as operator<.

    In set containers, the keys to sort the elements are the values
    themselves, therefore value_comp and its sibling member function key_comp
    are equivalent.
  */

  std::set<int> set{1, 2, 3, 4, 5};

  auto key_comp = set.key_comp();
  std::set<int> lt_3;
  std::set<int> ge_3;

  for (auto val : set) {
    if (key_comp(val, 3))
      lt_3.insert(val);
    else
      ge_3.insert(val);
  }
  ASSERT_THAT(lt_3, ElementsAre(1, 2));
  ASSERT_THAT(ge_3, ElementsAre(3, 4, 5));
}

TEST(TestStdset, LowerBound) {
  /*
    Returns an iterator pointing to the first element in the container which is
    not considered to go before val (i.e., either it is equivalent or goes
    after).
  */

  std::set<int> set{0, 10, 20, 30, 40, 50, 60, 70};
  auto it_lower = set.lower_bound(20);
  EXPECT_EQ(*it_lower, 20);

  it_lower = set.lower_bound(19);
  EXPECT_EQ(*it_lower, 20);

  it_lower = set.lower_bound(21);
  EXPECT_EQ(*it_lower, 30);
}

TEST(TestStdset, UpperBound) {
  /*
    Returns an iterator pointing to the first element in the container which is
    considered to go after val.
  */
  std::set<int> set{0, 10, 20, 30, 40, 50, 60, 70};
  auto it_upper = set.upper_bound(20);
  EXPECT_EQ(*it_upper, 30);

  it_upper = set.upper_bound(19);
  EXPECT_EQ(*it_upper, 20);

  it_upper = set.upper_bound(21);
  EXPECT_EQ(*it_upper, 30);

  auto it_lower = set.lower_bound(20);
  it_upper = set.upper_bound(50);
  EXPECT_EQ(*it_lower, 20);
  EXPECT_EQ(*it_upper, 60);

  set.erase(it_lower, it_upper);
  ASSERT_THAT(set, ElementsAre(0, 10, 60, 70));
}

TEST(TestStdset, CustomComparator) {
  /*
    Custom comparators can be used. For example assume a point compare;
  */
  // Preparations
  struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y){};
    // for matcher, ASSERT
    bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
  };

  // compare 2 points with respect to origin
  struct PointCmp {
    bool operator()(const Point& lhs, const Point& rhs) const {
      auto left = std::hypot(lhs.x, lhs.y);   // sqrt(2 ^ 2 + 5 ^ 2); (2,5)
      auto right = std::hypot(rhs.x, rhs.y);  // sqrt(3 ^ 2 + 4 ^ 2); (3,4)
      return left < right;  // 29 < 25 = false; so swap them. (3,4), (2,5)
    }
  };

  std::set<Point, PointCmp> set = {{2, 5}, {3, 4}, {1, 1}};
  ASSERT_THAT(set, ElementsAre(Point(1, 1), Point(3, 4), Point(2, 5)));

  set.emplace(1, -1);  // will be skipped
  set.emplace(10, 10);

  ASSERT_THAT(
      set, ElementsAre(Point(1, 1), Point(3, 4), Point(2, 5), Point(10, 10)));

  // Use predicate
  auto pred = [](const Point& lhs, const Point& rhs) {
    return std::hypot(lhs.x, lhs.y) < std::hypot(rhs.x, rhs.y);
  };

  std::set<Point, decltype(pred)> set2(pred);
  set2.emplace(Point{2, 5});
  set2.emplace(Point{3, 4});
  set2.emplace(Point{10, 10});
  set2.emplace(Point{1, 1});
  set2.insert({1, -1});
  set2.emplace(-1, 1);
  set2.emplace(Point(-1, -1));

  ASSERT_THAT(
      set2, ElementsAre(Point(1, 1), Point(3, 4), Point(2, 5), Point(10, 10)));
}
