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
  std::cout << "lowerbound 3.5 : " << tree2.find(3.5)->lowerbound()->get_key()
            << std::endl;
  std::cout << "upperbound 3.5 : " << tree2.find(3.5)->upperbound()->get_key()
            << std::endl;
  std::cout << "lowerbound 1.5 : " << tree2.find(1.5)->lowerbound()->get_key()
            << std::endl;
  std::cout << "lowerbound 1.5 : " << tree2.find(1.5)->upperbound()
            << std::endl;
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
  std::cout << "find a : " << (tree3.find("a") ? "true" : "false") << std::endl;
  std::cout << "find b : " << (tree3.find("b") ? "true" : "false") << std::endl;
  std::cout << "find c : " << (tree3.find("c") ? "true" : "false") << std::endl;
  std::cout << "find d : " << (tree3.find("d") ? "true" : "false") << std::endl;
  std::cout << "find e : " << (tree3.find("e") ? "true" : "false") << std::endl;
  std::cout << "find f : " << (tree3.find("f") ? "true" : "false") << std::endl;
  std::cout << "find g : " << (tree3.find("g") ? "true" : "false") << std::endl;
  std::cout << "find z : " << (tree3.find("z") ? "true" : "false") << std::endl;
  std::cout << "tree3 is balanced : " << (tree3.is_balanced()) << std::endl;
  std::cout << "tree3 is empty : " << (tree3.is_empty()) << std::endl;
  tree3.clear_tree();
  std::cout << "tree3 is empty : " << (tree3.is_empty()) << std::endl;

  std::cout << "hello" << std::endl;
}
