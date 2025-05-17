#include "../src/avltree.hpp"
#include <algorithm>
#include <gtest/gtest.h>
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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
