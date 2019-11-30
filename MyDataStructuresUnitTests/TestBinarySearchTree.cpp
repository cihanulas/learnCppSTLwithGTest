#include "pch.h"

#include "BinarySearcTree.h"
#include "gmock\gmock.h"

BinarySearchTree create_tree() {
  /*
          5
      1		9
   0    2   7  10

*/
  // Operation

  BinarySearchTree bst;
  bst.insert(5);
  bst.insert(1);
  bst.insert(9);

  bst.insert(0);
  bst.insert(2);
  bst.insert(10);
  bst.insert(7);

  return bst;
}

void static check_tree(const BinarySearchTree& bst) {
  // Tests
  auto root = bst.root();
  // check root
  EXPECT_EQ(root->value, 5);
  // Check Left of the root
  EXPECT_EQ(root->left->value, 1);
  EXPECT_EQ(root->left->left->value, 0);
  EXPECT_EQ(root->left->right->value, 2);
  // Check Left of the root
  EXPECT_EQ(root->right->value, 9);
  EXPECT_EQ(root->right->left->value, 7);
  EXPECT_EQ(root->right->right->value, 10);
}

MATCHER_P3(NodeIs, value, left, right, "Check Node") {
  bool res = arg->value == value && arg->left->value == left &&
             arg->right->value == right;
  return res;
}

MATCHER_P(NodeWithNoChild, value, "Check Node") {
  bool res =
      arg->value == value && arg->left == nullptr && arg->right == nullptr;
  return res;
}

MATCHER_P(NodeValue, value, "Check Node Value") { return arg->value == value; }
TEST(TestBinarySearchTree, Insert) {
  /*
  O(1):
  */
  // Preparations
  BinarySearchTree bst = create_tree();
  // Tests

  // check tree;
  check_tree(bst);
  // Insert an non-exsiting element
  EXPECT_TRUE(bst.insert(11));
  EXPECT_FALSE(bst.insert(0));
}

TEST(TestBinarySearchTree, Initializer) {
  // Use initializer list
  BinarySearchTree bst{5, 1, 9, 0, 2, 10, 7};
  check_tree(bst);
}
TEST(TestBinarySearchTree, LookUp) {
  /*
                5
            1		9
         0    2   7  10

  */

  BinarySearchTree bst = create_tree();

  auto elem1 = bst.lookup(1);
  ASSERT_THAT(elem1, NodeIs(1, 0, 2));

  auto elem2 = bst.lookup(7);
  ASSERT_THAT(elem2, NodeWithNoChild(7));
}

TEST(TestBinarySearchTree, Root) {
  BinarySearchTree bst;

  // Operation
  EXPECT_EQ(bst.root(), nullptr);
  bst.insert(3);
  ASSERT_THAT(bst.root(), NodeWithNoChild(3));

  BinarySearchTree bst_init(5);
  ASSERT_THAT(bst_init.root(), NodeWithNoChild(5));
}
