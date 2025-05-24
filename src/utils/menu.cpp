#include "menu.hpp"

void display_menu() {
  std::cout << "\033[2J\033[1;1H";
  std::cout << "\nAVL Tree Operations:\n";
  std::cout << "1. Insert key\n";
  std::cout << "2. Delete key\n";
  std::cout << "3. Clear tree\n";
  std::cout << "4. Insert vector\n";
  std::cout << "5. Exit\n";
  std::cout << "Enter choice (1-4): ";
}
