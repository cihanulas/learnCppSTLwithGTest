#pragma once

#include "Node.h"

class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  BinarySearchTree(int value) { insert(value); }
  BinarySearchTree(std::initializer_list<int> list) {
    for (auto it = list.begin(); it != list.end(); it++) {
      insert(*it);
    }
  }
  bool insert(int value) {
    auto new_node = createNode(value);
    if (!m_root) {
      m_root = new_node;
      return true;
    }

    auto current_node = m_root;

    BNodeSharedPtr prev;
    while (1) {
      auto previous_node = current_node;
      if (value < current_node->value) {
        if (current_node->left) {
          current_node = current_node->left;
        } else {
          current_node->left = new_node;
          return true;
        }
      } else if (value > current_node->value) {
        if (current_node->right) {
          current_node = current_node->right;
        } else {
          current_node->right = new_node;
          return true;
        }
      } else {
        return false;
      }
    }
  }

  BNodeSharedPtr lookup(int value) {
    auto ptr = m_root;
    while (ptr != nullptr) {
      if (value < ptr->value) {
        ptr = ptr->left;
      } else if (value > ptr->value) {
        ptr = ptr->right;
      } else {
        return ptr;
      }
    }
    return ptr;
  }
  BNodeSharedPtr root() { return m_root; }
  const BNodeSharedPtr root() const { return m_root; }

 private:
  BNodeSharedPtr createNode(int value) {
    return std::make_shared<BNode>(value, nullptr, nullptr);
  }
  BNodeSharedPtr m_root{nullptr};
};
