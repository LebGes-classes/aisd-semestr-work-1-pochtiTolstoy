#pragma once

#include "node.hpp"

template <typename T> class AVLTree {
public:
  AVLTree();
  ~AVLTree();

private:
  Node<T> *root_;
  size_t num_nodes_;
};
