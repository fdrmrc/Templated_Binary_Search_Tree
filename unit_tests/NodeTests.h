#include "../include/Node.h"
// #include <string>
//include the google test dependencies
#include <gtest/gtest.h>

TEST(nodeTesting, Node_Default_Constructor)
{
    Node<std::pair<int, int>> node;
    EXPECT_TRUE(node.right == nullptr) << "Node has not been properly initialized";
    EXPECT_TRUE(node.left == nullptr) << "Node has not been properly initialized";
    EXPECT_TRUE(node.parent == nullptr) << "Node has not been properly initialized";
}

TEST(nodeTesting, Node_Custom_Constructor_integers)
{
    Node<std::pair<int, int>> node(std::pair<int, int>(2, 3));
    EXPECT_EQ(node.data.first, 2);
    EXPECT_EQ(node.data.second, 3);
    EXPECT_TRUE(node.right == nullptr);
    EXPECT_TRUE(node.left == nullptr);
}

TEST(nodeTesting, Node_Custom_Constructor_strings)
{
    Node<std::pair<std::string, std::string>> node(std::pair<std::string, std::string>("first", "second"));
    EXPECT_EQ(node.data.first, "first");
    EXPECT_EQ(node.data.second, "second");
    EXPECT_TRUE(node.right == nullptr);
    EXPECT_TRUE(node.left == nullptr);
}

TEST(nodeTesting, Node_Constructor_With_Parent)
{

    std::pair<int, int> parent_pair(2, 2);
    std::pair<int, int> my_pair(3, 20);
    Node<std::pair<int, int>> parent_node(parent_pair);
    Node<std::pair<int, int>> node(my_pair, &parent_node);
    EXPECT_TRUE(node.parent == &parent_node);
    EXPECT_EQ(node.parent->data.first, parent_node.data.first);
    EXPECT_EQ(node.parent->data.second, parent_node.data.second);
}

TEST(nodeTesting, Multiple_Nodes)
{
    Node<std::pair<int, int>> head_node(std::pair<int, int>(10, 10), nullptr);
    head_node.right.reset(new Node<std::pair<int, int>>(std::pair<int, int>(2, 2), &head_node));
    Node<std::pair<int, int>> node{std::pair<int, int>(4, 4), head_node.right.get()};
    EXPECT_TRUE(node.parent->parent == &head_node);
    EXPECT_EQ(node.parent->parent->right->data.first, 2);
}

// int main(int argc, char **argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
