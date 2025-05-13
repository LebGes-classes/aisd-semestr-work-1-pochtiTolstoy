#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>

template <typename T> class AVLTree;

template <typename T> class Node {
  friend class AVLTree<T>;

public:
  Node(const T &key = T{}, int height = 0);
  ~Node();

  Node(const Node &) = delete;
  Node &operator=(const Node &) = delete;

  void set_height(int height);
  int get_height() const;
  int get_balance() const;
  void recalc_height();
  Node<T> *get_min() const;
  Node<T> *get_next() const;
  void display() const;

private:
  Node<T> *left_;
  Node<T> *right_;
  Node<T> *parent_;
  T key_;
  int height_;
};

template <typename T>
Node<T>::Node(const T &key, int height)
    : left_{nullptr}, right_{nullptr}, parent_{nullptr}, key_{key},
      height_{height} {}

template <typename T> Node<T>::~Node() {
  delete left_;
  delete right_;
}

template <typename T> void Node<T>::set_height(int height) { height_ = height; }

template <typename T> int Node<T>::get_height() const { return height_; }

template <typename T> Node<T> *Node<T>::get_min() const {
  Node<T> *current = this;
  while (current->left_) {
    current = current->left_;
  }
  return current;
}

template <typename T> Node<T> *Node<T>::get_next() const {
  if (right_) {
    return get_min(right_);
  }
  Node<T> *current = this;
  Node<T> *parent = parent_;
  while (parent && current != parent->left_) {
    current = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename T> void Node<T>::recalc_height() {
  int left_height = (left_) ? left_->get_height() : 0;
  int right_height = (right_) ? right_->get_height() : 0;
  height_ = 1 + std::max(left_height, right_height);
}

template <typename T> int Node<T>::get_balance() const {
  int left_height = (left_) ? left_->get_height() : 0;
  int right_height = (right_) ? right_->get_height() : 0;
  return left_height - right_height;
}

template <typename T> void Node<T>::display() const {
  std::cout << key_ << " ";
}

template <typename T> void display_node(const Node<T> *node) {
  node->display();
}
