#include "avltree.hpp"
#include <iostream>

int main() {
  AVLTree<int> tree;
  tree.display();
  tree.insert(10);
  tree.insert(2);
  tree.insert(11);
  tree.display();
  std::cout << "tree is balanced : " << (tree.is_balanced() ? "true" : "false")
            << std::endl;

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
  std::cout << "tree2 is balanced : "
            << (tree2.is_balanced() ? "true" : "false") << std::endl;

  AVLTree<std::string> tree3;
  tree3.insert("a");
  tree3.insert("b");
  tree3.insert("c");
  tree3.insert("d");
  tree3.insert("e");
  tree3.insert("f");
  tree3.insert("g");
  tree3.insert("h");
  tree3.display();
  std::cout << "tree3 is balanced : "
            << (tree3.is_balanced() ? "true" : "false") << std::endl;
  std::cout << "hello" << std::endl;
}
