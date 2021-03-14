#include "../include/bst.h"
#include <gtest/gtest.h>

TEST(IteratorTests, custom_constructor)
{
    std::pair<int, int> my_pair{8, 8};
    Node<std::pair<int, int>> node{my_pair, nullptr};
    auto it{_iterator<std::pair<int, int>, false>{&node}};
    EXPECT_EQ(it.current, &node);
}

TEST(IteratorTests, default_constructor)
{
    auto it{_iterator<std::pair<int, int>, false>{}};
    EXPECT_EQ(it.current, nullptr);
}

TEST(IteratorTests, double_pre_increment)
{
    std::pair<int, int> parent_pair{8, 8};
    std::pair<int, int> ten_pair{10, 10};
    std::pair<int, int> frteen_pair{14, 14};
    std::pair<int, int> twenty_pair{20, 20};
    Node<std::pair<int, int>> parent_node{parent_pair, nullptr};

    parent_node.right.reset(new Node<std::pair<int, int>>(frteen_pair));
    parent_node.left.reset(new Node<std::pair<int, int>>(ten_pair));

    parent_node.right->right.reset(new Node<std::pair<int, int>>(twenty_pair));
    auto it = _iterator<std::pair<int, int>, false>(&parent_node);
    auto itpp = ++(++it);
    EXPECT_EQ(itpp->first, twenty_pair.first);
}

TEST(IteratorTests, non_constness_check)
{
    std::pair<int, int> parent_pair{8, 8};
    Node<std::pair<int, int>> parent_node{parent_pair, nullptr};
    auto it{_iterator<std::pair<int, int>, false>{&parent_node}};
    it->first = 20;
    it->second = 30;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, 30);
}

TEST(IteratorTests, equality_check)
{
    std::pair<int, int> parent_pair{8, 8};
    Node<std::pair<int, int>> parent_node{parent_pair, nullptr};
    auto it_non_const{_iterator<std::pair<int, int>, false>{&parent_node}};
    auto it_const{_iterator<std::pair<int, int>, true>{&parent_node}};
    EXPECT_TRUE(it_const.operator==(it_non_const)); //we expect true because they're iterators to the same node
}
TEST(IteratorTests, inequality_check)
{
    std::pair<int, int> first_pair{8, 8};
    std::pair<int, int> second_pair{10, 10};
    Node<std::pair<int, int>> node1{first_pair, nullptr};
    Node<std::pair<int, int>> node2{second_pair, nullptr};
    auto it_non_const{_iterator<std::pair<int, int>, false>{&node1}};
    auto it_const{_iterator<std::pair<int, int>, true>{&node2}};
    EXPECT_TRUE(it_const.operator!=(it_non_const));
}

TEST(IteratorTests, post_increment)
{
    std::pair<int, int> parent_pair{8, 8};
    std::pair<int, int> frteen_pair{14, 14};
    Node<std::pair<int, int>> parent_node{parent_pair, nullptr};

    parent_node.right.reset(new Node<std::pair<int, int>>(frteen_pair));

    auto it = _iterator<std::pair<int, int>, false>(&parent_node);
    auto itpp = it.operator++(1);
    EXPECT_EQ(itpp->first, parent_pair.first);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}