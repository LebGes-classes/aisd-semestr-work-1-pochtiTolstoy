#include "avltree.hpp"
#include <iostream>

int main() {
  AVLTree<int> tree;
  tree.display();
  tree.insert(10);
  tree.insert(2);
  tree.insert(11);
  tree.display();

  AVLTree<double> tree2;
  tree2.insert(4.5);
  tree2.insert(1.5);
  tree2.insert(2.5);
  tree2.insert(3.5);
  tree2.insert(4.6);
  tree2.insert(1.5);
  tree2.insert(2.8);
  tree2.insert(3.9);
  tree2.display();
  std::cout << "hello" << std::endl;
}
