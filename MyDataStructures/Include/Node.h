#pragma once
#include <memory>
struct Node {
  Node(int val) : value(val) {}
  Node(int val, std::shared_ptr<Node> nxt) : value(val), next(nxt) {}

  int value{-1};
  std::shared_ptr<Node> next{nullptr};
};
using NodeSharedPtr = std::shared_ptr<Node>;

struct BNode {
  BNode(int val) : value(val) {}
  BNode(int val, std::shared_ptr<BNode> left_, std::shared_ptr<BNode> right_)
      : value(val), left(left_), right(right_) {}

  int operator->() const { return value; }

  int value{-1};
  std::shared_ptr<BNode> left{nullptr};
  std::shared_ptr<BNode> right{nullptr};
};
using BNodeSharedPtr = std::shared_ptr<BNode>;
