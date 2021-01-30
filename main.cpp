#include "include/bst.h"


int main() {
    
    std::cout << "**First tests with Nodes** \n";
    Node<double> test_node{2.0}; //all the pointers (both raw and smart) are nullptr
    Node<double> test_copy_cstr{2.0, &test_node};
    
    
    //Test with pairs of integers
    using intpair = std::pair<int, int>; //for sake of readability
    
    std::pair<int, int> parent_pair{8, 8};
    Node<intpair> parent_node{parent_pair,nullptr};
    std::pair<int, int> elf_pair{11,11};
    parent_node.right = std::unique_ptr<Node<intpair>> {new Node<intpair> {elf_pair, &parent_node}};
    std::pair<int,int> nine_pair{9,9};
    std::pair<int, int> ten_pair{10,10};
    std::pair<int, int> frteen_pair{14,14};
    
    parent_node.right->right = std::unique_ptr<Node<intpair>> {new Node<intpair> {frteen_pair,parent_node.right.get()}};
    parent_node.right->left = std::unique_ptr<Node<intpair>> {new Node<intpair> {ten_pair,parent_node.right.get()}};
    parent_node.right->left->left = std::unique_ptr<Node<intpair>> {new Node<intpair> {nine_pair,parent_node.right->left.get()}};
    
    parent_node.print();
    parent_node.right->print(); //printing test
    parent_node.right->left->print();
    
    auto it{__iterator<intpair>(&parent_node)};
    auto itpp{++it};
    std::cout << "Expect next node's value: " << nine_pair.second <<". \t"<<"Obtained: " << itpp->second <<"\n";
    
    auto it2{__iterator<intpair>(parent_node.right->left.get())}; //Node with key and value equal to 10
    auto it2pp{++it2};
    std::cout <<"Expected next Node's value: " << elf_pair.second << ". \t" <<"Obtained: "<< it2pp->second<<"\n";
    
    
    
    std::cout << "** TESTS WITH THE TREE IN EXAM'S TEST**" << "\n";
    bst<int, int> my_tree{}; //created empty tree
    auto f = my_tree.insert(intpair{8,8});
    auto g = my_tree.insert(intpair{3,3});
    auto h = my_tree.insert(intpair{10,10});
    auto i = my_tree.insert(intpair{1,1});
    auto l = my_tree.insert(intpair{6,6});
    auto m = my_tree.insert(intpair{4,4});
    auto n = my_tree.insert(intpair{7,7});
    auto o = my_tree.insert(intpair{14,14});
    auto p = my_tree.insert(intpair{13,13});
    
    
    
    std::cout <<"Put-to operator test: "<< my_tree <<"\n";
    
    return 0;
}
