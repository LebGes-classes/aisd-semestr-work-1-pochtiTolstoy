#include "../src/avltree.hpp"
#include <algorithm>
#include <chrono>
#include <gtest/gtest.h>
#include <memory>
#include <random>
#include <vector>

class AVLTreeTest : public ::testing::Test {
protected:
  void SetUp() override { tree = new AVLTree<int>(); }

  void TearDown() override { delete tree; }

  AVLTree<int> *tree;
};

// Test empty tree properties
TEST_F(AVLTreeTest, EmptyTree) {
  EXPECT_TRUE(tree->is_empty());
  EXPECT_EQ(tree->get_size(), 0);
  EXPECT_EQ(tree->get_min(), nullptr);
  EXPECT_EQ(tree->get_max(), nullptr);
  EXPECT_EQ(tree->find(5), nullptr);
}

// Test insertion and basic properties
TEST_F(AVLTreeTest, BasicInsertion) {
  tree->insert(5);
  EXPECT_FALSE(tree->is_empty());
  EXPECT_EQ(tree->get_size(), 1);
  EXPECT_EQ(tree->find(5)->get_key(), 5);
  EXPECT_EQ(tree->get_min()->get_key(), 5);
  EXPECT_EQ(tree->get_max()->get_key(), 5);
}

// Test multiple insertions and tree balance
TEST_F(AVLTreeTest, MultipleInsertions) {
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 17};
  for (int val : values) {
    tree->insert(val);
  }

  EXPECT_EQ(tree->get_size(), values.size());
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_EQ(tree->get_min()->get_key(), 3);
  EXPECT_EQ(tree->get_max()->get_key(), 17);
}

// Test deletion
TEST_F(AVLTreeTest, Deletion) {
  tree->insert(10);
  tree->insert(5);
  tree->insert(15);

  tree->delete_key(5);
  EXPECT_EQ(tree->get_size(), 2);
  EXPECT_EQ(tree->find(5), nullptr);
  EXPECT_TRUE(tree->is_balanced());

  tree->delete_key(10);
  EXPECT_EQ(tree->get_size(), 1);
  EXPECT_EQ(tree->find(10), nullptr);
  EXPECT_TRUE(tree->is_balanced());
}

// Test tree traversals
TEST_F(AVLTreeTest, Traversals) {
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 17};
  for (int val : values) {
    tree->insert(val);
  }

  std::vector<int> in_order = tree->in_order();
  std::vector<int> pre_order = tree->pre_order();
  std::vector<int> post_order = tree->post_order();

  std::sort(values.begin(), values.end());
  EXPECT_EQ(in_order, values);

  // Verify pre-order and post-order have correct size
  EXPECT_EQ(pre_order.size(), values.size());
  EXPECT_EQ(post_order.size(), values.size());
}

// Test lower and upper bounds
TEST_F(AVLTreeTest, Bounds) {
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 17};
  for (int val : values) {
    tree->insert(val);
  }

  Node<int> *lower = tree->lowerbound(8);
  EXPECT_NE(lower, nullptr);
  EXPECT_EQ(lower->get_key(), 10);

  Node<int> *upper = tree->upperbound(8);
  EXPECT_NE(upper, nullptr);
  EXPECT_EQ(upper->get_key(), 7);
}

// Test tree balancing with sequential insertions
TEST_F(AVLTreeTest, SequentialInsertions) {
  for (int i = 1; i <= 100; ++i) {
    tree->insert(i);
    EXPECT_TRUE(tree->is_balanced());
    EXPECT_EQ(tree->get_size(), i);
  }
}

// Test tree balancing with random insertions
TEST_F(AVLTreeTest, RandomInsertions) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 1000);

  for (int i = 0; i < 100; ++i) {
    int val = dis(gen);
    tree->insert(val);
    EXPECT_TRUE(tree->is_balanced());
  }
}

// Test clear tree functionality
TEST_F(AVLTreeTest, ClearTree) {
  for (int i = 1; i <= 10; ++i) {
    tree->insert(i);
  }

  EXPECT_EQ(tree->get_size(), 10);
  tree->clear_tree();
  EXPECT_TRUE(tree->is_empty());
  EXPECT_EQ(tree->get_size(), 0);
  EXPECT_EQ(tree->get_min(), nullptr);
  EXPECT_EQ(tree->get_max(), nullptr);
}

// Test duplicate insertions
TEST_F(AVLTreeTest, DuplicateInsertions) {
  tree->insert(5);
  tree->insert(5);
  EXPECT_EQ(tree->get_size(), 1);
  EXPECT_EQ(tree->find(5)->get_key(), 5);
}

// Test height property
TEST_F(AVLTreeTest, HeightProperty) {
  tree->insert(10);
  EXPECT_EQ(tree->get_height(), 1);

  tree->insert(5);
  tree->insert(15);
  EXPECT_EQ(tree->get_height(), 2);

  tree->insert(3);
  tree->insert(7);
  tree->insert(12);
  tree->insert(17);
  EXPECT_EQ(tree->get_height(), 3);
}

// Test stress with large number of operations
TEST_F(AVLTreeTest, StressTest) {
  const int num_operations = 10000;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, num_operations);

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < num_operations; ++i) {
    int val = dis(gen);
    tree->insert(val);
    EXPECT_TRUE(tree->is_balanced());
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  // Verify tree properties after stress test
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_LE(tree->get_height(), 2 * std::log2(tree->get_size() + 1));
}

// Test deletion of all nodes
TEST_F(AVLTreeTest, DeleteAllNodes) {
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 17};
  for (int val : values) {
    tree->insert(val);
  }

  for (int val : values) {
    tree->delete_key(val);
    EXPECT_TRUE(tree->is_balanced());
  }

  EXPECT_TRUE(tree->is_empty());
  EXPECT_EQ(tree->get_size(), 0);
}

// Test tree properties after multiple deletions
TEST_F(AVLTreeTest, MultipleDeletions) {
  // Insert a complete binary tree
  for (int i = 1; i <= 15; ++i) {
    tree->insert(i);
  }

  // Delete nodes in a specific pattern
  std::vector<int> to_delete = {8, 4, 12, 2, 6, 10, 14};
  for (int val : to_delete) {
    tree->delete_key(val);
    EXPECT_TRUE(tree->is_balanced());
  }

  // Verify remaining nodes
  std::vector<int> remaining = {1, 3, 5, 7, 9, 11, 13, 15};
  for (int val : remaining) {
    EXPECT_NE(tree->find(val), nullptr);
  }
}

// Test tree properties with negative numbers
TEST_F(AVLTreeTest, NegativeNumbers) {
  std::vector<int> values = {-10, -5, -15, -3, -7, -12, -17};
  for (int val : values) {
    tree->insert(val);
  }

  EXPECT_EQ(tree->get_size(), values.size());
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_EQ(tree->get_min()->get_key(), -17);
  EXPECT_EQ(tree->get_max()->get_key(), -3);
}

// Test tree properties with mixed positive and negative numbers
TEST_F(AVLTreeTest, MixedNumbers) {
  std::vector<int> values = {-10, 5, -15, 3, -7, 12, -17};
  for (int val : values) {
    tree->insert(val);
  }

  EXPECT_EQ(tree->get_size(), values.size());
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_EQ(tree->get_min()->get_key(), -17);
  EXPECT_EQ(tree->get_max()->get_key(), 12);
}

// Test tree properties after clearing and reinserting
TEST_F(AVLTreeTest, ClearAndReinsert) {
  // First insertion
  for (int i = 1; i <= 10; ++i) {
    tree->insert(i);
  }

  // Clear tree
  tree->clear_tree();
  EXPECT_TRUE(tree->is_empty());

  // Reinsert in different order
  for (int i = 10; i >= 1; --i) {
    tree->insert(i);
  }

  EXPECT_EQ(tree->get_size(), 10);
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_EQ(tree->get_min()->get_key(), 1);
  EXPECT_EQ(tree->get_max()->get_key(), 10);
}

// Test tree properties with repeated clear and insert operations
TEST_F(AVLTreeTest, RepeatedClearAndInsert) {
  for (int iteration = 0; iteration < 5; ++iteration) {
    // Insert numbers
    for (int i = 1; i <= 10; ++i) {
      tree->insert(i);
    }

    EXPECT_EQ(tree->get_size(), 10);
    EXPECT_TRUE(tree->is_balanced());

    // Clear tree
    tree->clear_tree();
    EXPECT_TRUE(tree->is_empty());
  }
}

// Test tree properties with large numbers
TEST_F(AVLTreeTest, LargeNumbers) {
  const int max_value = 1000000;
  std::vector<int> values = {max_value, max_value / 2, max_value / 4,
                             max_value / 8};

  for (int val : values) {
    tree->insert(val);
  }

  EXPECT_EQ(tree->get_size(), values.size());
  EXPECT_TRUE(tree->is_balanced());
  EXPECT_EQ(tree->get_min()->get_key(), max_value / 8);
  EXPECT_EQ(tree->get_max()->get_key(), max_value);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
