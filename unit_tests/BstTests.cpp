#include "../include/bst.h"
#include <gtest/gtest.h>

TEST(TreeTests, insertion)
{
    bst<const int, int> tree{};
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
    bst<const int, int> tree{};
    auto ins = tree.insert(std::pair<const int, int>{8, 8});
    auto ins2 = tree.insert(std::pair<const int, int>{2, 2});
    auto ins3 = tree.insert(std::pair<const int, int>{1, 1});
    auto ins4 = tree.insert(std::pair<const int, int>{3, 3});
    auto ins5 = tree.insert(std::pair<const int, int>{6, 6});

    bst<const int, int> tree2{};
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

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
