#pragma once
#include <memory>
struct Node {
  Node(int val) : value(val) {}
  Node(int val, std::shared_ptr<Node> nxt) : value(val), next(nxt) {}

  int operator->() const { return value; }

  int value{-1};
  std::shared_ptr<Node> next{nullptr};
};
using NodeSharedPtr = std::shared_ptr<Node>;
