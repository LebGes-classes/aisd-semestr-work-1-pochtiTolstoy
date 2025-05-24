#pragma once

#include "../avltree/avltree.hpp"
#include <iostream>
#include <limits>
#include <sstream>

void display_menu();

template <typename T> bool handle_operation(AVLTree<T> &tree) {
  int choice;
  T key;
  display_menu();
  if (!(std::cin >> choice)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please enter a number.\n";
    return true;
  }

  bool running = true;
  switch (choice) {
  case 1: {
    std::cout << "Enter integer to insert: ";
    while (!(std::cin >> key)) {
      std::cout << "Invalid input. Enter integer: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    tree.insert(key);
    std::cout << "Inserted " << key << "\n";
    break;
  }
  case 2: {
    std::cout << "Enter integer to delete: ";
    while (!(std::cin >> key)) {
      std::cout << "Invalid input. Enter integer: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    tree.delete_key(key);
    std::cout << "Deleted " << key << "\n";
    break;
  }
  case 3: {
    tree.clear_tree();
    std::cout << "Tree cleared\n";
    break;
  }
  case 4: {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter numbers separated by spaces: ";
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    T num;
    size_t count = 0;

    while (iss >> num) {
      tree.insert(num);
      count++;
    }
    if (iss.fail() && !iss.eof()) {
      std::string bad_input;
      iss.clear();
      iss >> bad_input;
      std::cout << "Warning: Skipped invalid input '" << bad_input << "'\n";
    }
    std::cout << "Inserted " << count << " values\n";
    break;
  }
  case 5: {
    std::cout << "Exiting...\n";
    tree.clear_tree();
    running = false;
    break;
  }
  default:
    std::cout << "Invalid choice. Try again.\n";
    break;
  }
  return running;
}
