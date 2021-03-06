#include "include/bst.h"

void test_with_constant_find_function(const bst<int, int> &bst)
{
    // simple test function to check that the const version of find works properly
    bst.find(10);
}

int main()
{ 

    std::cout << "**First tests with Nodes** \n";
    Node<double> test_node{2.0}; //all the pointers (both raw and smart) are nullptr
    Node<double> test_copy_cstr{2.0, &test_node};

    //Test with pairs of integers
    using intpair = std::pair<int, int>; //for sake of readability

    std::pair<int, int> parent_pair{8, 8};
    Node<intpair> parent_node{parent_pair, nullptr};
    std::pair<int, int> elf_pair{11, 11};

    parent_node.right = std::unique_ptr<Node<intpair>>{new Node<intpair>{elf_pair, &parent_node}};
    std::pair<int, int> nine_pair{9, 9};
    std::pair<int, int> ten_pair{10, 10};
    std::pair<int, int> frteen_pair{14, 14};

    parent_node.right->right = std::unique_ptr<Node<intpair>>{new Node<intpair>{frteen_pair, parent_node.right.get()}};
    parent_node.right->left = std::unique_ptr<Node<intpair>>{new Node<intpair>{ten_pair, parent_node.right.get()}};
    parent_node.right->left->left.reset(new Node<intpair>{nine_pair, parent_node.right->left.get()});

    parent_node.print();
    parent_node.right->print(); //printing test
    parent_node.right->left->print();

    auto it{_iterator<intpair, false>(&parent_node)};
    it->first = 96; //good that it's allowed
    (*it).second = 2;
    // auto itpp{it++}; //post - increment
    auto itpp{++it}; //pre - increment
    std::cout << "Expect next node's value: " << nine_pair.second << ". \t"
              << "Obtained: " << itpp->second << "\n";

    auto it2{_iterator<intpair, false>(parent_node.right->left.get())}; //Node with key and value equal to 10
    auto it2pp{++it2};
    //    it2->first=2; //if the bool in the iterator is set to true, then we have an error because we're modifying
    std::cout << "Expected next Node's value: " << elf_pair.second << ". \t"
              << "Obtained: " << it2pp->second << "\n";

    auto test_equality_iterator{_iterator<intpair, false>(&parent_node)};
    auto test_equality_iterator2{_iterator<intpair, true>(&parent_node)};
    bool is_equal{test_equality_iterator2 == test_equality_iterator};
    bool is_notequal{test_equality_iterator != test_equality_iterator2};
    std::cout << "Test for iterator(s) equality: " << is_equal << "\n"
              << "Test for operator inequality: " << is_notequal << "\n";

    std::cout << "** TESTS WITH THE TREE IN EXAM'S TEST **"
              << "\n";

    bst<int, int> my_tree{}; //created empty tree
    auto f = my_tree.insert(intpair{8, 8});
    auto g = my_tree.insert(intpair{3, 3});
    auto h = my_tree.insert(intpair{10, 10});
    auto i = my_tree.insert(intpair{1, 1});
    auto l = my_tree.insert(intpair{6, 6});
    auto m = my_tree.insert(intpair{4, 4});
    auto n = my_tree.insert(intpair{7, 7});
    auto o = my_tree.insert(intpair{14, 14});
    auto p = my_tree.insert(intpair{13, 13});
    auto m2 = my_tree.insert(intpair{4, 4});

    std::cout << "Put-to operator test: " << my_tree << std::endl;

    std::cout << "** TESTS WITH A RANDOM-GENERATED TREE **"
              << "\n";
    bst<int, int> rand_tree{};
    srand(time(NULL)); //random seed
    int rd_value{};
    for (int i = 0; i <= 10; ++i)
    {
        rd_value = std::rand() % 50;
        auto it = rand_tree.insert(intpair{rd_value, rd_value});
    }
    std::cout << rand_tree << "\n";

    std::cout << "** FIND TESTS with DETERMINISTIC TREE **"
              << "\n";

    auto fd{rand_tree.find(8)};
    test_with_constant_find_function(rand_tree);

    std::cout << "** OPERATOR[] TESTS **"
              << "\n";
    int lvalueint{40};
    my_tree[5] = 5; //my_tree.operator[](5)
    my_tree[lvalueint] = lvalueint;

    my_tree.operator[](lvalueint) = lvalueint;

    std::cout << my_tree << "\n";

    std::cout << "** EMPLACE TESTS ** "
              << "\n";
    auto e1{my_tree.emplace(90, 90)};
    std::cout << my_tree << "\n";

    std::cout << "** TEST COPY SEMANTICS ** "
              << "\n";

    std::cout << "DEEP COPY"
              << "\n";
    bst<int, int> test_bst_copy_semantics{rand_tree};
    std::cout << "original: " << rand_tree << "\n"
              << " copied: " << test_bst_copy_semantics << "\n";

    std::cout << "COPY ASSIGNMENT"
              << "\n";
    test_bst_copy_semantics = my_tree;
    std::cout << "Now it is \n"
              << test_bst_copy_semantics << "\n";
    auto ins_3 = test_bst_copy_semantics.insert(std::pair<int, int>(12, 12)); //r-value insertion
    std::cout << "Let's insert something to check the deepness of the copy: \n"
              << test_bst_copy_semantics << "\n and the origina is \n"
              << my_tree << "\n";

    std::cout << "** TEST MOVE SEMANTICS** "
              << "\n";
    std::cout << "MOVE CONSTRUCTOR"
              << "\n";
    bst<int, int> test_bst_move_semantics{std::move(my_tree)}; //move cstr
    std::cout << "Original, after been stolen: \n"
              << my_tree << "has been moved to: \n"
              << test_bst_move_semantics << "\n";

    std::cout << "MOVE ASSIGNMENT"
              << "\n";
    std::cout << "Before stealing: \n"
              << rand_tree << "\n";
    test_bst_move_semantics = std::move(rand_tree); //move assignment
    std::cout << "Original, after been stolen: \n"
              << rand_tree << "has been moved to \n"
              << test_bst_move_semantics << "\n";

    std::cout << "BALANCE TESTS: "
              << "\n";
    bst<int, int> tobebalanced{};
    for (int i = 1; i <= 6; ++i)
    {
        tobebalanced.insert(intpair{i, i});
    }
    std::cout << tobebalanced << "\n";

    tobebalanced.balance();
    bool is_bal{tobebalanced.is_balanced()};
    std::cout << "Is it balanced? " << is_bal << "\n";
    //    tobebalanced.unordered_print();

    std::cout << "Let's balance the random tree"
              << "\n";
    test_bst_move_semantics.balance();
    std::cout << "Is it balanced? " << test_bst_move_semantics.is_balanced() << "\n";

    my_tree.clear();
    rand_tree.clear();
    test_bst_copy_semantics.clear();
    test_bst_move_semantics.clear();

    std::cout << "ERASURE TESTS: "
              << "\n";
    bst<int, int> erasure_test{tobebalanced}; //copy constructor call
    
    std::cout << "Before erasing: " <<erasure_test <<"\n";
    erasure_test.erase(4);                    //Here the key corresponds to the key of the head

    std::cout << "Removed Node with key=4: " << erasure_test << "\n";

    bst<int, int> erasure_test2{};
    auto er1{erasure_test2.insert(intpair(5, 5))};
    auto er2{erasure_test2.insert(intpair(2, 2))};
    auto er3{erasure_test2.insert(intpair(12, 12))};
    auto er4{erasure_test2.insert(intpair(3, 3))};
    auto er5{erasure_test2.insert(intpair(9, 9))};
    auto er6{erasure_test2.insert(intpair(21, 21))};
    auto er7{erasure_test2.insert(intpair(19, 19))};
    auto er8{erasure_test2.insert(intpair(25, 25))};

    std::cout << "Before erasing: " << erasure_test2 << "\n";
    erasure_test2.erase(12);

    std::cout << "After erasing node with key = 12: " << erasure_test2 << "\n";

    bst<int, int> erasure_test3{};
    auto ert1{erasure_test3.insert(intpair(8, 8))};
    auto ert2{erasure_test3.insert(intpair(6, 6))};
    auto ert3{erasure_test3.insert(intpair(10, 10))};
    auto ert4{erasure_test3.insert(intpair(9, 9))};
    auto ert5{erasure_test3.insert(intpair(11, 11))};
    auto ert6{erasure_test3.insert(intpair(3, 3))};
    auto ert7{erasure_test3.insert(intpair(7, 7))};
    //    auto ert6{erasure_test3.insert(intpair(12,12))};

    try
    {
        erasure_test3.erase(8);
        erasure_test3.erase(60);
    }
    catch (const key_not_found &s)
    {
        std::cerr << s.what() << "\n";
    }

    std::cout << "Let's build another tree where the successor is the next one and has NO child"
              << "\n";
    bst<int, int> tree_for_test_3{};
    auto test_next1{tree_for_test_3.emplace(8, 8)};
    auto test_next2{tree_for_test_3.emplace(9, 9)};
    auto test_next3{tree_for_test_3.emplace(3, 3)};
    auto test_next4{tree_for_test_3.emplace(1, 1)};
    auto test_next5{tree_for_test_3.emplace(6, 6)};
    std::cout << "Our new tree is: " << tree_for_test_3 << "\n";
    tree_for_test_3.erase(8);
    std::cout << "After removing Key 8 (head node), my_tree becomes \n"
              << tree_for_test_3 << std::endl;

    bst<int, int> provamia{};
    auto provain{provamia.insert(std::pair<int, int>(9, 9))};
    provamia.erase(9);
    std::cout << provamia << "\n";

    std::cout << "Let's build another tree where the successor is the next one and has child"
              << "\n";
    bst<int, int> tree_for_test_2{};
    auto test_erasure1{tree_for_test_2.emplace(8, 8)};
    auto test_erasure2{tree_for_test_2.emplace(9, 9)};
    auto test_erasure_next{tree_for_test_2.emplace(10, 10)};
    auto test_erasure3{tree_for_test_2.emplace(3, 3)};
    auto test_erasure4{tree_for_test_2.emplace(1, 1)};
    auto test_erasure5{tree_for_test_2.emplace(6, 6)};
    std::cout << "Our new tree is: " << tree_for_test_2 << "\n";
    tree_for_test_2.erase(8);
    std::cout << "After removing Key 8 (head node), my_tree becomes \n"
              << tree_for_test_2 << std::endl;

    std::cout << "Let's build another tree where the successor has a right child"
              << "\n";
    bst<int, int> tree_for_test{};
    auto test11{tree_for_test.emplace(8, 8)};
    auto test22{tree_for_test.emplace(3, 3)};
    auto test3{tree_for_test.emplace(1, 1)};
    auto test4{tree_for_test.emplace(6, 6)};
    auto test5{tree_for_test.emplace(20, 20)};
    auto test6{tree_for_test.emplace(21, 21)};
    auto test7{tree_for_test.emplace(9, 9)};
    auto test8{tree_for_test.emplace(10, 10)}; //successor of key 9
    std::cout << "Our new tree is: " << tree_for_test << "\n";
    std::cout << "Case: two children and successor is NOT the next one AND has right child"
              << "\n";
    tree_for_test.erase(8);
    std::cout << "After removing Key 8 (head node), my_tree becomes \n"
              << tree_for_test << std::endl;

    rand_tree.clear();
    std::cout << rand_tree << "\n";

    return 0;
}