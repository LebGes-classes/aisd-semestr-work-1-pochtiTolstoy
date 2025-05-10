#pragma once

#include <cstdlib>

template <typename T> class Node {
public:
  Node(const T &key = T{}, size_t height = 0) : key_{key}, height_{height} {}

  Node(const Node<T> &) = delete;
  Node<T> &operator=(const Node<T> &) = delete;

  ~Node() {
    delete left_;
    delete right_;
  };

  size_t get_height() const { return height_; }

  Node<T> *get_minimum() {
    Node<T> *current = this;
    while (current->left_) {
      current = current->left_;
    }
    return current;
  }

  Node<T> *get_next() {
    if (right_) {
      return right_->get_minimum();
    }
    Node<T> *current = this;
    Node<T> *parent = parent_;
    while (parent && current != parent->left_) {
      current = parent;
      parent = parent->parent_;
    }
    return parent;
  }

private:
  T key_;
  Node<T> *left_;
  Node<T> *right_;
  Node<T> *parent_;
  size_t num_keys_;
  size_t height_;
};
