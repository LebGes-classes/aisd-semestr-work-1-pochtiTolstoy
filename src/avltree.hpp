#pragma once

#include "node.hpp"
#include <cstdlib>

#define MAX_BALANCE_TRESHOLD 1
#define MIN_BALANCE_TRESHOLD -1

template <typename T> class AVLTree {
public:
  AVLTree();
  ~AVLTree();
  void clear_tree();
  size_t get_size() const;
  void insert(const T &key);
  size_t get_height() const;
  void display() const;
  bool is_balanced() const;

private:
  Node<T> *insert_recursively(Node<T> *, const T &);
  Node<T> *fix_balance(Node<T> *, const T &);
  Node<T> *RR_rotate(Node<T> *);
  Node<T> *RL_rotate(Node<T> *);
  Node<T> *LL_rotate(Node<T> *);
  Node<T> *LR_rotate(Node<T> *);
  void traverse_inorder(Node<T> *node, void (*func)(const Node<T> *)) const;
  bool is_balanced_(const Node<T> *node) const;

  Node<T> *root_;
  size_t size_;
};

template <typename T> AVLTree<T>::AVLTree() : root_{nullptr}, size_{0} {}

template <typename T> AVLTree<T>::~AVLTree() { delete root_; }

template <typename T> void AVLTree<T>::clear_tree() {
  delete root_;
  root_ = nullptr;
  size_ = 0;
}

template <typename T> size_t AVLTree<T>::get_size() const { return size_; }

template <typename T> size_t AVLTree<T>::get_height() const {
  return root_->get_height();
}

template <typename T> void AVLTree<T>::insert(const T &key) {
  Node<T> *node = insert_recursively(root_, key);
  if (node != nullptr) {
    root_ = node;
  }
}

template <typename T>
Node<T> *AVLTree<T>::insert_recursively(Node<T> *node, const T &key) {
  /* 1. Going down.
   *
   * We will recursively go down the tree,
   * until we find a correct place for a new node.
   *
   */

  /* found place for new node */
  if (node == nullptr) {
    ++size_;
    return new Node<T>(key, 0);
  }

  /* if the same key was found in an existing node,
   * then the tree structure should remain the same
   */
  if (key == node->key_) {
    return node;
  }

  if (key < node->key_) {
    /* Let's try to find a place for a new node in the left subtree */
    node->left_ = insert_recursively(node->left_, key);

    /* Fix parent of returned node */
    node->left_->parent_ = node;
  } else if (key > node->key_) {
    /* Let's try to find a place for a new node in the right subtree */
    node->right_ = insert_recursively(node->right_, key);

    /* Fix parent of returned node, perfectly works with balance */
    node->right_->parent_ = node;
  }

  /* 2. Going up.
   *
   * From this moment we have found a place for the new node,
   * and now we begin to climb up the recursion and gradually
   * correct the balance in the nodes until we reach the root.
   *
   */

  /* Recalculate new height of given node */
  node->recalc_height();

  return fix_balance(node, key);
}

template <typename T>
Node<T> *AVLTree<T>::fix_balance(Node<T> *node, const T &key) {
  /* LL-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the left subtree
   * of the left child of our node.
   *
   */
  if (node->get_balance() > MAX_BALANCE_TRESHOLD && node->left_ &&
      key < node->left_->key_) {
    return LL_rotate(node); /* parent should be fixed in caller */
  }

  /* RR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree
   * of the right child of our node.
   *
   */
  if (node->get_balance() < MIN_BALANCE_TRESHOLD && node->right_ &&
      key > node->right_->key_) {
    return RR_rotate(node); /* parent should be fixed in caller */
  }

  /* LR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree
   * of the left child of our node.
   *
   */
  if (node->get_balance() > MAX_BALANCE_TRESHOLD && node->left_ &&
      key > node->left_->key_) {
    return LR_rotate(node); /* parent should be fixed in caller */
  }

  /* RL-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the left subtree
   * of the right child of our node.
   *
   */
  if (node->get_balance() < MIN_BALANCE_TRESHOLD && node->right_ &&
      key < node->right_->key_) {
    return RL_rotate(node); /* parent should be fixed in caller */
  }

  return node; /* if no rotates are needed */
}

// single rotate - turn x counter clockwise
template <typename T> Node<T> *AVLTree<T>::RR_rotate(Node<T> *x) {
  if (x->right_ == nullptr)
    return x;

  // clang-format off
  //  x          y  
  //   \        / \
  //    y  =>  x   ?
  //   / \      \
  //  z   ?      z
  // clang-format on

  Node<T> *y = x->right_; // save subtree
  Node<T> *z = y->left_;  // save subtree

  y->left_ = x;
  x->right_ = z;

  x->parent_ = y;
  y->parent_ = nullptr; // y - root or will be fixed in caller
  if (z != nullptr) {
    z->parent_ = x;
  }

  // recalc height : x - first, y - second
  x->recalc_height();
  y->recalc_height();

  return y;
}

// single rotate - turn x clockwise
template <typename T> Node<T> *AVLTree<T>::LL_rotate(Node<T> *x) {
  if (x->left_ == nullptr) {
    return x;
  }

  // clang-format off
  //     x       y  
  //    /       / \
  //   y   =>  ?   x
  //  / \         /
  // ?   z       z
  // clang-format on

  Node<T> *y = x->left_;  // save subtree
  Node<T> *z = y->right_; // save subtree

  y->right_ = x;
  x->left_ = z;

  x->parent_ = y;
  y->parent_ = nullptr;
  if (z != nullptr) {
    z->parent_ = x;
  }

  // recalc height : x - first, y - second
  x->recalc_height();
  y->recalc_height();

  return y;
}

// double rotate
template <typename T> Node<T> *AVLTree<T>::RL_rotate(Node<T> *node) {
  node->right_ = LL_rotate(node->right_); // turn right child clockwise
  node->right_->parent_ = node;           // fix parent
  return RR_rotate(node);                 // parent should be fixed in caller
}

// double rotate
template <typename T> Node<T> *AVLTree<T>::LR_rotate(Node<T> *node) {
  node->left_ = RR_rotate(node->left_); // turn left child counter clockwise
  node->left_->parent_ = node;          // fix parent
  return LL_rotate(node);               // parent should be fixed in caller
}

template <typename T> void AVLTree<T>::display() const {
  if (root_ == nullptr) {
    return;
  }
  traverse_inorder(root_, display_node);
  std::cout << std::endl;
}

template <typename T>
void AVLTree<T>::traverse_inorder(Node<T> *node,
                                  void (*func)(const Node<T> *)) const {
  if (node == nullptr) {
    return;
  }
  traverse_inorder(node->left_, func);
  func(node);
  traverse_inorder(node->right_, func);
}

template <typename T> bool AVLTree<T>::is_balanced() const {
  return is_balanced_(root_);
}

template <typename T> bool AVLTree<T>::is_balanced_(const Node<T> *node) const {
  if (node == nullptr)
    return true;
  int balance = node->get_balance();
  if (balance < MIN_BALANCE_TRESHOLD || balance > MAX_BALANCE_TRESHOLD) {
    return false;
  }
  return is_balanced_(node->left_) && is_balanced_(node->right_);
}
