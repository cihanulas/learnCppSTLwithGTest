#pragma once
#include <functional>
// #include <utility>
#include "Node.h"

class LinkedList {
 public:
  LinkedList() {}
  LinkedList(int value) { add_first_item(value); }
  LinkedList(std::initializer_list<int> v) {
    for (auto it = v.begin(); it != v.end(); it++) {
      push_back(*it);
    }
  }

  void push_back(int value) {
    if (empty()) {
      add_first_item(value);
      return;
    }

    // get the current tail

    auto new_node = createNode(value);
    m_tail->next = new_node;

    updateTail(new_node);
    m_length++;
  };

  void push_front(int value) {
    if (empty()) {
      add_first_item(value);
      return;
    }

    // get the current tail

    auto new_node = createNode(value);
    new_node->next = m_head;

    updateHead(new_node);
    m_length++;
  };

  void pop_back() {
    if (empty()) {
      return;
    }

    // if head tail are pointing to same node.
    if (m_head == m_tail) {
      m_head.reset();
      m_tail.reset();
      m_head = nullptr;
      m_tail = nullptr;
      m_length = 0;
      return;
    }

    // get the current tail
    auto ptr = head();
    while (ptr->next != m_tail) {
      ptr = ptr->next;
    }

    // delete ptr->next.get();
    ptr->next.reset();
    ptr->next = nullptr;

    updateTail(ptr);
    m_length--;
  };

  void pop_front() {
    if (empty()) {
      return;
    }

    // get the current tail
    auto ptr = m_head;
    auto next_node = m_head->next;
    m_head.reset();

    updateHead(next_node);
    m_length--;
  };

  /*
  {0 1 3 4}
  insert (2,10) // insert to index 2
  {0 1 10 3 4}
  */
  void insert(size_t index, int value) {
    if (index == 0) {
      push_front(value);
      return;
    } else if (index > m_length - 1) {  // just add at the end.
      push_back(value);
      return;
    }

    NodeSharedPtr prev_node = node_at(index - 1);
    NodeSharedPtr next_node = prev_node->next;
    auto new_node = createNode(value);

    prev_node->next = new_node;
    new_node->next = next_node;
    m_length++;
  }

  void erase(size_t index) {
    if (index >= m_length - 1)
      return pop_back();
    else if (index <= 0)
      return pop_front();

    auto prev_node = node_at(index - 1);
    deleteNodeViaPrevNode(prev_node);
  }

  template <class _Pr1>
  void remove_if(_Pr1 eval) {
    while (eval(m_head->value)) {
      pop_front();
    }

    auto current_node = m_head;
    auto prev_node = m_head;
    while (current_node != nullptr) {
      if (eval(current_node->value)) {
        m_tail = prev_node;
        deleteNodeViaPrevNode(prev_node);
      }
      prev_node = current_node;
      current_node = current_node->next;
    }
  };

  void remove(int val) {
    remove_if([val](int value) { return value == val; });
  }

  void reverse() {
    // [10, 12, 0, 4] => [4, 0, 12, 10] watch the video. It is quite
    // complicated.s https:// www.geeksforgeeks.org/reverse-a-linked-list/
    if (!m_head->next) return;

    m_tail = m_head;

    auto first = m_head;        // first = {10, &12}
    auto second = first->next;  // second = {12, &0}

    while (second) {
      auto temp = second->next;  // temp = {0, }		,
      second->next = first;      // second = {12, &10}
      first = second;            // first = {12, &10}
      second = temp;             // second = {0, }
    }
    m_head->next = nullptr;
    m_head = first;
  }

  NodeSharedPtr begin() { return m_head; }
  NodeSharedPtr end() { return m_tail; }
  NodeSharedPtr node_at(size_t index) {
    auto ptr = head();
    int i = 0;
    while (ptr != nullptr && i < index) {
      ptr = ptr->next;
      i++;
    }
    return ptr;
  }
  int at(size_t index) { return node_at(index)->value; }
  bool empty() { return m_length == 0; }
  friend void print(LinkedList list);
  friend NodeSharedPtr next(LinkedList& list, size_t index = 0);

 private:
  NodeSharedPtr head() { return m_head; }
  NodeSharedPtr head() const {
    return m_head;
  }  // for const object, which can not modify the head
  size_t size() const { return m_length; }
  // bool operator==(const LinkedList& rhs) const { return true; }

 private:
  void add_first_item(int value) {
    m_head = createNode(value);
    m_tail = m_head;
    m_length++;
  }

  NodeSharedPtr createNode(int value) { return std::make_shared<Node>(value); }

  void updateTail(NodeSharedPtr new_node) { m_tail = new_node; }
  void updateHead(NodeSharedPtr new_node) { m_head = new_node; }
  void deleteNodeViaPrevNode(NodeSharedPtr prev_node) {
    auto node_to_delete = prev_node->next;
    prev_node->next = node_to_delete->next;
    node_to_delete.reset();
    m_length--;
  }

 private:
  NodeSharedPtr m_head{nullptr};
  NodeSharedPtr m_tail{nullptr};
  size_t m_length{0};
};

namespace std {
NodeSharedPtr next(NodeSharedPtr ptr, size_t index = 1) {
  NodeSharedPtr temp = ptr;
  size_t i = 0;
  while (i < index) {
    temp = temp->next;
    i++;
  }
  return temp;
};

void print(const LinkedList& list) { return; };

}  // namespace std
// void static printList(const LinkedList& list, const std::string& title = "")
// {
//  NodeSharedPtr ptr = list.head();
//
//  std::cout << title << std::endl;
//  while (ptr != nullptr) {
//    std::cout << ptr->value << " ";
//    ptr = ptr->next;
//  }
//  std::cout << std::endl;
//}
//
// void static printList(const std::list<int>& list,
//                      const std::string& title = "") {
//  std::cout << title << std::endl;
//  for (auto it = list.begin(); it != list.end(); it++) {
//    std::cout << *it << " ";
//  }
//  std::cout << std::endl;
//}

/*
No Value

Head=Tail=null;
append(value_1);
Head={value1, null};
Tail&=Head


append(value_2);
Node_1= {value_2, nullptr}
Head={value1, &Node_1};
Tail&=Node_1

append(value_3);
Node_2= {value_3, nullptr}
Head={value1, &Node_1};
Node_1={value_3, &Node_2}
Tail&=Node_2

*/
