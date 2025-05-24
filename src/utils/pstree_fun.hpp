#pragma once

#include <string>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "../avltree/node.hpp"

template <typename T> class PstreeDisplay final {
public:
  static pid_t run_pstree_display(const AVLTree<T> &tree) {
    pid_t pid = fork();
    if (pid == 0) {
      setpgid(0, 0);
      create_process_hierarchy(tree.root_);
      _exit(0);
    }
    return pid;
  }

private:
  static void set_process_name(int value) {
    std::string name = "AVL-" + std::to_string(value);
    prctl(PR_SET_NAME, name.c_str()); // limit 16 chars
  }

  static void create_process_hierarchy(Node<T> *node) {
    if (!node)
      return;
    const unsigned int sleep_time = 1000;
    set_process_name(node->key_);
    std::vector<pid_t> children;
    auto fork_child = [&](Node<T> *child_node) {
      pid_t pid = fork();
      if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
      }
      if (pid == 0) {
        create_process_hierarchy(child_node);
        sleep(sleep_time);
        _exit(0);
      } else {
        children.push_back(pid);
      }
    };
    if (node->right_) {
      fork_child(node->right_);
    }
    if (node->left_) {
      fork_child(node->left_);
    }
    for (pid_t c : children) {
      int status;
      waitpid(c, &status, 0);
    }
    sleep(sleep_time);
  }

  PstreeDisplay() = delete;
  ~PstreeDisplay() = delete;
};
