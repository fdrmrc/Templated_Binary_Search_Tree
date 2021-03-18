#include "../include/bst.h"
#include <gtest/gtest.h>

template <typename key_type, typename value_type>
void tree_generator(bst<key_type, value_type> &tree)
{
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});
    auto ins6 = tree.insert(std::pair<const int, int>{9, 9});
    auto ins7 = tree.insert(std::pair<const int, int>{10, 10});
    auto ins8 = tree.insert(std::pair<const int, int>{11, 11});
    auto ins9 = tree.insert(std::pair<const int, int>{15, 15});
    auto ins10 = tree.insert(std::pair<const int, int>{12, 12});
}

TEST(TreeTests, insertion)
{
    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{2, 2});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    EXPECT_EQ(ins.first->second, 2);
    EXPECT_EQ(ins2.second, false); //since the key is already preseent
}

TEST(TreeTests, copy_constructor)
{
    bst<const int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});

    bst<const int, int> tree2{tree};
    auto start = tree2.cbegin();
    auto original_it = tree.cbegin();
    for (auto it = start; it != tree2.cend(); ++it)
    {
        EXPECT_EQ(it->second, original_it->second);
        ++original_it; //increment the original tree
    }
    auto ins_new_tree{tree2.insert(std::pair<int, int>{10, 10})};
    EXPECT_FALSE(tree.find(10) == tree2.find(10)); //I want to modify only tree2
}

TEST(TreeTests, copy_assignment)
{
    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});

    bst<int, int> tree2{};
    auto ins6 = tree2.insert(std::pair<const int, int>{20, 20}); //initialize tree2 with a pair
    tree2 = tree;                                                //copy assignment is called

    auto start = tree2.cbegin();
    auto original_it = tree.cbegin();
    for (auto it = start; it != tree2.cend(); ++it)
    {
        EXPECT_EQ(it->second, original_it->second);
        ++original_it; //increment the original tree
    }
    auto ins_check = tree2.insert(std::pair<const int, int>{30, 30});
    EXPECT_FALSE(tree.find(30) == tree2.find(30)); //I want to modify only tree2

    std::cout << tree2 << "\t" << tree << std::endl; //visualize the difference
}

TEST(TreeTests, move_constructor)
{
    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});

    bst<int, int> tree2{std::move(tree)};
    EXPECT_FALSE(tree.find(8) == tree2.find(8)); //I want to modify only tree2
}

TEST(TreeTests, move_assignment)
{
    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});

    bst<int, int> tree2{};
    auto ins6 = tree2.insert(std::pair<const int, int>{20, 20}); //initialize tree2 with a pair
    tree2 = std::move(tree);                                     //move assignment is called

    EXPECT_FALSE(tree.find(8) == tree2.find(8)); //I want to modify only tree2
}

TEST(TreeTests, emplace_test)
{
    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});
    EXPECT_FALSE(tree.emplace(2, 2).second); //pair 2,2 is already present
    EXPECT_TRUE(tree.emplace(10, 10).second);
}

TEST(TreeTests, balance_tests)
{

    bst<int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});
    tree.balance();
    EXPECT_TRUE(tree.is_balanced());
    bst<int, int> tree2{}; //another test
    for (size_t i = 0; i < 20; i++)
    {
        tree2[i] = i; //fill the tree
    }
    tree2.balance();
    EXPECT_TRUE(tree2.is_balanced());
}

TEST(Tree_Tests, erasure_test_leaf_node)
{

    bst<int, int> tree{};
    tree_generator(tree); //fill the empty tree
    tree.erase(12);
    auto null_iterator = _iterator<std::pair<const int, int>, false>{nullptr}; //used to compare with find function
    EXPECT_EQ(tree.find(12), null_iterator);
}

TEST(Tree_Tests, erasure_test_one_child)
{
    bst<int, int> tree_3{};
    tree_generator(tree_3);
    tree_3.erase(10);
    auto it2{++(tree_3.find(9))};
    EXPECT_EQ(it2->first, 11);
    EXPECT_EQ((++it2)->first, 12);
    EXPECT_EQ((++it2)->first, 15);
}

TEST(Tree_Tests, erasure_test_two_children)
{

    bst<int, int> tree_3{};
    tree_generator(tree_3);
    tree_3.erase(10);
    auto it2{++(tree_3.find(9))};
    EXPECT_EQ(it2->first, 11);
    EXPECT_EQ((++it2)->first, 12);
    EXPECT_EQ((++it2)->first, 15);
}