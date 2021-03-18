#ifndef bst_h
#define bst_h

#include "Iterator.h"
#include <functional> //std::less
#include <utility>    //std::make_pair
#include <vector>
#include <time.h> //to generate a random tree and change the seed
/** @mainpage
 *
 * In the following some brief descriptions of the classes involved in the project. 
 * @section section1 Description
 * A templated binary search tree implemented in C++ (compliant with the C++14 standard). The project is split into three files, each one of them contains the implementation of concept, and hence in each one of them we have a class declaration and definition.
 *
 * @subsection subsection1 Node.h
 * The implementation of the concept of a Node. A Node is templated on the type of the value, which in this project will be a `std::pair` with a key and a value, and must know its children and its parent. Therefore we have 4 data member. The pointers to the left and right child are `unique_ptr`, while the pointer to the parent is a raw pointer. If it were a `unique_ptr`, then we would end up with nodes that are pointed (uniquely) by more pointers, which is not correct.
 *
 * @subsection subsection2 Iterator.h
 * The class iterator is templated on the type 'T' of the Node, and on a boolean 'is_const', used to determine the const-ness of the iterator by exploiting `std::conditional`, a C++11 which determines at compile time the types of a member. The most important operator is the '++' (pre-increment), which allows to go the next (ordering by key) @ref Node by returning a self-reference.
 *
 * @subsection subsection3 bst.h
 * This class contains the implementation of the Binary Search Tree. It's templated on the type of the key, on the type of the value, and on the type of the comparison operator, which is set to `std::less` by default. The data members are a `std::unique_ptr` to the head Node, and the comparison operator.
 *
 *
 */

/**
 * @brief Struct used in the error-handling of the `erase` function. It'll be catched in a try-catch block.
 * 
 * */

struct key_not_found
{
    /**
     * @brief The string with the message  
     */
    std::string s;
    /**
     * @brief Custom constructor
     * @param _s String to be printed  
     */
    key_not_found(std::string _s) : s{_s} {};

    /**
     * @brief Classical method to show the error message in the try-catch block
     */
    const char *what() const
    {
        return s.c_str();
    }
};

template <typename key_type, typename value_type, typename OP = std::less<key_type>>
class bst
{

    /**
     * @brief a pair with a constant `key` and a value.
     */
    using pair_type = std::pair<const key_type, value_type>;
    /**
     * @brief Templated Node
     */
    using node_type = Node<pair_type>;

    /**
     * @brief iterator templated on @ref node_type and on @ref pair_type
     */
    using iterator = _iterator<pair_type, false>;
    /**
     * @brief iterator that points to a constant content (i.e. the @ref pair_type). It can be increased/decreased, but not used to modify the tree. Notice that it's the pair that is constant!
     */
    using constant_iterator = _iterator<pair_type, true>;

private:
    /**
    * @brief Comparison operator. By default, it's set to `std::less<key_type>`. It is used to compare the keys of our tree
    */
    OP comp;                         //std::less<key_type> comp;

    /**
     * @brief Unique pointer to the head @ref Node. 
     */
    std::unique_ptr<node_type> head; //unique pointer to the root/head Node
    //I set the head to be a unique pointer so I can use release,get,reset member fcts

    /**
     * @brief Helper recursive function used in the copy constructor to perform a deep copy.
     * @param ptn reference to a `std::unique_ptr`
     *
     */
    /*
    void copy_helper(std::unique_ptr<Node<pair_type>>& ptn) {
        this->insert(ptn.get()->data);
        if (ptn.get()->left) {
            copy_helper(ptn.get()->left);
        }
        if (ptn.get()->right) {
            copy_helper(ptn.get()->right);
        }
        return;
    }
    */

    /**
     * @brief Helper recursive function that finds the height of a @ref Node.
     * @param ptn Raw pointer to the Node of which we want to find the height.
     * The height is the number of nodes along the longest path from the node down to the farthest leaf node.
     */
    int get_height(Node<pair_type> *ptn)
    {
        if (!ptn)
        {
            return 0; //if is nullptr, height is 0
        }
        return 1 + std::max(get_height(ptn->left.get()), get_height(ptn->right.get()));
    }

    /**
     * @brief Helper recursive function that checks if the tree is balanced.
     * @param head_node Raw pointer to a @ref Node, which will be the @ref head Node. Since it's a unique pointer, we need to call it with `head.get()`.
     * Recall that a tree is balanced if, <b>for each </b> @ref Node, the height of the left and right subtree is at most 1 and each subtree of the tree is balanced.
     */
    bool balance_check(Node<pair_type> *head_node)
    {
        if (!head_node)
        {
            return true; //empy tree is balanced by definition
        }
        int left_height{get_height(head_node->left.get())};
        int right_height{get_height(head_node->right.get())};

        if (std::abs(left_height - right_height) <= 1 && balance_check(head_node->left.get()) && balance_check(head_node->right.get()))
        {
            return true;
        }

        return false;
    }

    /**
     * @brief Utility function used for @ref find(). It prevents code duplication since the body of @ref find() is almost the same if we do the lookup in a constant tree or not.
     */

    node_type *find_helper(const key_type &x) const
    {
        auto ptr{head.get()};
        while (ptr)
        {
            if (comp(x, ptr->data.first))
            {
                ptr = ptr->left.get();
            }
            else if (comp(ptr->data.first, x))
            {
                ptr = ptr->right.get();
            }
            else
            { //equality holds
                return ptr;
            }
        }
        return nullptr;
    }

    /**
     * @brief Helper (recursive) function to balance the tree.
     * @param v reference to a constant std::vector
     * @param a constant long int. Left bound of the subtree
     * @param b constant long int. Right bound of the subtree
     * Given a vector v with the (ordered) pairs of a tree, it balances the tree by inserting recursively the middle node, until this makes sense
     */

    void balance_helper(const std::vector<pair_type> &v, long int a, long int b)
    {
        if (a > b)
        {
            //            std::exception("Tree is not balancable");
            //            std::cout<< "Not possible" <<"\n";
            return;
        }
        else
        {
            int middle{static_cast<int>((a + b) / 2)};
            this->insert(v[middle]);
            balance_helper(v, a, middle - 1);
            balance_helper(v, middle + 1, b);
        }
    }

    /**
     * @brief Helper function used in @ref insert() that exploit forwarding reference to take both l-values and r-values references. Code duplication is hence avoided. In this way the user can just call the @ref insert() function and doesn't have to care about the type of the argument.
     * @param x Forwarding reference with the 'pair_type' to be inserted.
     * @see insert()
     */
    template <typename O>
    std::pair<iterator, bool> insert_helper(O &&x)
    {
        auto ptr{head.get()};
        while (ptr)
        {
            if (comp(x.first, ptr->data.first))
            {
                if (ptr->left)
                {
                    ptr = ptr->left.get();
                }
                else
                {
                    ptr->left.reset(new Node<pair_type>{std::forward<O>(x), ptr});
                    return std::make_pair<iterator, bool>(iterator{ptr->left.get()}, true);
                }
            }
            else if (comp(ptr->data.first, x.first))
            {
                if (ptr->right)
                {
                    ptr = ptr->right.get();
                }
                else
                {
                    ptr->right.reset(new Node<pair_type>{std::forward<O>(x), ptr});
                    return std::make_pair<iterator, bool>(iterator{ptr->right.get()}, true);
                }
            }
            else
            {
                return std::make_pair<iterator, bool>(iterator{ptr}, false);
            }
        }
        head.reset(new Node<pair_type>{std::forward<O>(x), nullptr});
        return std::make_pair<iterator, bool>(iterator{head.get()}, true);
    }

    /**
     * @brief Helper private function that uses forwarding references for the subscript operator.
     * @param x Forwarding reference, to be forwarded using `std::forward<O>(x)`
     * @see @ref operator[]
     */
    template <typename O> //forwarding reference
    value_type &subscript_helper(O &&x)
    {
        auto isfound = find_helper(std::forward<O>(x));
        if (isfound)
        {
            return isfound->data.second;
        }
        else
        { //key not found in tree
            auto a = pair_type{std::forward<O>(x), value_type{}};
            return insert(a).first->second; //l-value semantic used since a is a named object
        }
    }

public:
    /**
     * @brief Default constructor for the tree.
     */
    bst() : comp{}, head{nullptr} {}

    /**
     * @brief Move constructor. Avoiding the default-generated one for didactit purposes.
     */
    bst(bst &&t) noexcept : comp{std::move(t.comp)}, head{std::move(t.head)}
    {
        //        t.clear();
    }

    /**
     * @brief Move assignment. Avoiding the default-generated one for didactit purposes.
     */
    bst &operator=(bst &&t) noexcept
    {
        comp = std::move(t.comp);
        head = std::move(t.head);
        //        t.clear();
        return *this;
    }

    /* Uncomment to use the default-generated (and recommended) version
     bst(bst&& t) noexcept  = default;
     
     bst& operator=(bst&& t) noexcept = default; */

    /**
     * @brief Copy constructor.
     */
    explicit bst(const bst &tree) : comp{tree.comp}
    {
        //        head=std::make_unique<Node<pair_type>>(tree.head,nullptr);
        head = std::unique_ptr<Node<pair_type>>(new Node<pair_type>(tree.head, nullptr)); //call to recursive function in Node.h
    }

    /**
     * @brief Copy assignment.
     */
    bst &operator=(const bst &tree)
    {
        this->clear();
        this->comp = tree.comp;
        this->head = std::make_unique<Node<pair_type>>(tree.head, nullptr);
        return *this;
    }

    //    explicit bst(const bst& tree): comp{tree.comp},head{std::unique_ptr<Node<pair_type>> (new Node<pair_type>(tree.head.get()->data,nullptr))  } {
    //        if (tree.head.get()->left) {
    //            copy_helper(tree.head.get()->left);
    //        }
    //        if (tree.head.get()->right) {
    //            copy_helper(tree.head.get()->right);
    //        }
    //    }

    //    bst& operator=(const bst& tree) {
    ////        std::cout << "Call to copy assignment";
    //        this->clear();
    //        this->insert(tree.head.get()->data);
    //        if (tree.head.get()->left) {
    //            copy_helper(tree.head.get()->left);
    //        }
    //        if (tree.head.get()->right) {
    //            copy_helper(tree.head.get()->right);
    //        }
    //        return *this;
    //    }

    /**
     * @brief Returns an @ref Iterator to the first @ref Node of the tree, which is the leftmost.
     */
    iterator begin() noexcept
    {
        //        std::cout << "Calling begin" <<"\n";
        if (!head)
        {
            return iterator{nullptr};
        }
        auto ptr{head.get()};
        while (ptr->left)
        {
            ptr = ptr->left.get();
        }
        return iterator{ptr};
    }

    /**
     * @brief Returns a @ref constant_iterator to the first @ref Node of the tree. It's automatically applied when the tree is const-qualified and I call @ref begin()
     */

    constant_iterator begin() const noexcept
    {
        //        std::cout << "Calling const begin" <<"\n";
        if (!head)
        {
            return constant_iterator{nullptr};
        }
        auto ptr{head.get()};
        while (ptr->left)
        {
            ptr = ptr->left.get();
        }
        return constant_iterator{ptr};
    }

    /**
     * @brief Returns a @ref constant_iterator to the first @ref Node of the tree. It must be used unconditionally when the tree is const-qualified.
     */
    constant_iterator cbegin() const noexcept
    {
        //        std::cout << "Calling cbegin" <<"\n";
        if (!head)
        {
            return constant_iterator{nullptr};
        }
        auto ptr{head.get()};
        while (ptr->left)
        {
            ptr = ptr->left.get();
        }
        return constant_iterator{ptr};
    }

    /**
     * @brief Returns a constant @ref Iterator to one-past-the-last @ref Node of the tree.
     */
    iterator end() noexcept
    {
        //        std::cout << "Calling end" <<"\n";
        return iterator{nullptr};
    }

    /**
     * @brief Returns a @ref constant_iterator to one-past-the-last @ref Node of the tree. It's automatically applied when the tree is const-qualified and I call @ref end.
     */
    constant_iterator end() const noexcept
    {
        //        std::cout <<"Calling  const end"<< "\n";
        return constant_iterator{nullptr};
    }

    /**
     * @brief Returns a constant @ref Iterator to one-past-the-last @ref Node of the tree. It must be used unconditionally when the tree is const-qualified.
     */
    constant_iterator cend() const noexcept
    {
        //        std::cout <<"Calling cend"<< "\n";
        return constant_iterator{nullptr};
    }

    /**
     *
     * @brief Insert a new @ref Node in the tree with pair x
     * @param x Const l-value reference to a pair with a key and a value
     * Returns a std::pair with an @ref _iterator and a bool which is true if the node has been inserted, false otherwise.
     */
    std::pair<iterator, bool> insert(const pair_type &x)
    {
        //    std::cout <<"l-value insert"<<"\n";
        return insert_helper(x);
    }

    /**
     * @brief Insert a new @ref Node in the tree with pair x
     * @param x r-value reference to a pair with a node and a value
     * Returns a std::pair with an @ref _iterator and a bool which is true if the node has been inserted, false otherwise.
     */

    std::pair<iterator, bool> insert(pair_type &&x)
    {
        //    std::cout <<"r-value insert"<<"\n";
        return insert_helper(std::move(x));
    }

    /**
     * @brief Inserts a new element into the container constructed in-place with the given args if there is no element with the key in the container.
     * @param args arguments to be *unpacked*
     * It's like if we apply ‘std::forward<Types>(args)‘ to each element of the pair.
     */
    template <class... Types> //packing all the arguments
    std::pair<iterator, bool> emplace(Types &&...args)
    { //forwarding reference
        //verbose, but possibly clearer
        //        pair_type to_be_inserted{pair_type{std::forward<Types>(args)...}};
        //        return insert(to_be_inserted); //call to l-value!
        return insert(pair_type{std::forward<Types>(args)...});
    }

    /**
     * @brief Find a given key. If it's present, returns a @ref _iterator to the node with that key, otherwise @ref end(). It uses the helper function @ref find_helper to avoid code duplication
     * @param x The key to be searched in the tree.
     */
    iterator find(const key_type &x)
    {
        return iterator{find_helper(x)};
    }

    /**
     * @brief Find a given key in a constant tree. If it's present, returns a @ref iterator to the node with that key, otherwise @ref end(). It uses the helper function @ref find_helper to avoid code duplication
     * @param x The key to be searched in the tree.
     */
    constant_iterator find(const key_type &x) const
    {
        // std::cout << "Call to constant find" << "\n";
        return constant_iterator{find_helper(x)};
    }

    /**
     * @brief Erase a @ref Node in the tree
     * @param x constant reference to a key
     */

    void erase(const key_type &x)
    {
        auto it{find(x)};
        node_type *locator{it.current};
        if (!(it).current)
        {
            throw key_not_found{"Couldn't find a Node with key = " + std::to_string(x)};
        }

        if (locator == head.get())
        {
            if (!locator->right && !locator->left)
            { //no child case
                head.reset(nullptr);
            }
            else if (!(!locator->left) != !(!locator->right))
            { // 1 child only
                if (locator->right)
                { //child is the right one
                    head.reset(locator->right.release());
                    locator->right->parent = nullptr;
                }
                else
                { //child is the left one
                    head.reset(locator->left.release());
                    locator->left->parent = nullptr;
                }
            }
            else
            { //2 children case
                auto successor = (++it).current;
                auto DN = std::unique_ptr<Node<pair_type>>(new Node<pair_type>(successor->data, nullptr));
                DN->left.reset(locator->left.release());
                DN->left->parent = DN.get();
                if (successor == locator->right.get())
                {
                    DN->right.reset(successor->right.release());
                    if (DN->right)
                    { //if successor has a right chidl
                        DN->right->parent = DN.get();
                    }
                }
                else
                { //successor is NOT the next one
                    DN->right.reset(locator->right.release());
                    DN->right->parent = DN.get();
                    if (successor->right)
                    { //successor has right child
                        successor->right->parent = successor->parent;
                        successor->parent->left.reset(successor->right.release());
                    }
                    else
                    { //successor is a leaf
                        successor->parent->left.reset();
                    }
                }

                head.reset(DN.release());
            }
        }
        else
        { //the node to be deleted is not the head

            if (!(locator->left) && !(locator->right))
            {
                if (locator == locator->parent->left.get())
                {
                    locator->parent->left.reset();
                }
                else
                {
                    locator->parent->right.reset();
                }
            }
            else if (!(!locator->left) != !(!locator->right))
            {
                if (locator->left)
                {
                    locator->left->parent = locator->parent;
                    if (locator == locator->parent->left.get())
                    {
                        locator->parent->left.reset(locator->left.release());
                    }
                    else
                    {
                        locator->parent->right.reset(locator->left.release());
                    }
                }
                else
                {
                    locator->right->parent = locator->parent;
                    if (locator == locator->parent->left.get())
                    {
                        locator->parent->left.reset(locator->right.release());
                    }
                    else
                    {
                        locator->parent->right.reset(locator->right.release());
                    }
                }
            }
            else
            {
                ++it;
                node_type *successor{it.current};

                if (successor != locator->right.get())
                {
                    auto DNP{locator->parent};                                                            // DNP := the pointer to the parent of the node to be deleted
                    auto DN{std::unique_ptr<Node<pair_type>>(new Node<pair_type>(successor->data, DNP))}; // DN := the unique pointer to the newly created node which contains the successor's data
                    erase(successor->data.first);

                    DN->left.reset(locator->left.release()); // locator := the pointer to the node to be deleted
                    DN->left->parent = DN.get();
                    DN->right.reset(locator->right.release());
                    DN->right->parent = DN.get();

                    if (locator == DNP->left.get())
                    {
                        DNP->left.reset(DN.release());
                    }
                    else
                    {
                        DNP->right.reset(DN.release());
                    }
                }
                else
                {
                    successor->left.reset(locator->left.release());
                    successor->left->parent = successor;
                    erase(locator->data.first);
                }
            }
        }
        // std::cout << "LOCATION OF LOCATOR " << &locator << "\n";
    }

    // void erase(const key_type &x)
    // {
    //     //exception handling: TODO
    //     auto it{find(x)};
    //     if (!(it).current)
    //     {
    //         throw key_not_found{"Couldn't find a Node with key = " + std::to_string(x)};
    //     }

    //     node_type *locator{it.current};

    //     if (locator == head.get())
    //     {
    //         if (!locator->right && !locator->left)
    //         { //no child case
    //             head.reset(nullptr);
    //         }
    //         else if (!(!locator->left) != !(!locator->right))
    //         { // 1 child only
    //             if (locator->right)
    //             { //child is the right one
    //                 head.reset(locator->right.release());
    //                 locator->right->parent = nullptr;
    //             }
    //             else
    //             { //child is the left one
    //                 head.reset(locator->left.release());
    //                 locator->left->parent = nullptr;
    //             }
    //         }
    //         else
    //         { //2 children case
    //             auto successor = (++it).current;
    //             auto DN = std::unique_ptr<Node<pair_type>>(new Node<pair_type>(successor->data, nullptr));
    //             DN->left.reset(locator->left.release());
    //             DN->left->parent = DN.get();
    //             if (successor == locator->right.get())
    //             {
    //                 DN->right.reset(successor->right.release());
    //                 if (DN->right)
    //                 { //if successor has a right chidl
    //                     DN->right->parent = DN.get();
    //                 }
    //             }
    //             else
    //             { //successor is NOT the next one
    //                 DN->right.reset(locator->right.release());
    //                 DN->right->parent = DN.get();
    //                 if (successor->right)
    //                 { //successor has right child
    //                     successor->right->parent = successor->parent;
    //                     successor->parent->left.reset(successor->right.release());
    //                 }
    //                 else
    //                 { //successor is a leaf
    //                     successor->parent->left.reset();
    //                 }
    //             }

    //             head.reset(DN.release());
    //         }
    //     }
    //     else
    //     { //the node to be deleted is not the head

    //         if (!(locator->left) && !(locator->right))
    //         {
    //             if (locator == locator->parent->left.get())
    //             {
    //                 locator->parent->left.reset();
    //             }
    //             else
    //             {
    //                 locator->parent->right.reset();
    //             }
    //         }
    //         else if (!(!locator->left) != !(!locator->right))
    //         {
    //             if (locator->left)
    //             {
    //                 locator->left->parent = locator->parent;
    //                 if (locator == locator->parent->left.get())
    //                 {
    //                     locator->parent->left.reset(locator->left.release());
    //                 }
    //                 else
    //                 {
    //                     locator->parent->right.reset(locator->left.release());
    //                 }
    //             }
    //             else
    //             {
    //                 locator->right->parent = locator->parent;
    //                 if (locator == locator->parent->left.get())
    //                 {
    //                     locator->parent->left.reset(locator->right.release());
    //                 }
    //                 else
    //                 {
    //                     locator->parent->right.reset(locator->right.release());
    //                 }
    //             }
    //         }
    //         else
    //         {
    //             ++it;
    //             node_type *successor{it.current};

    //             if (successor != locator->right.get())
    //             {
    //                 auto DNP{locator->parent};                                                            // DNP := the pointer to the parent of the node to be deleted
    //                 auto DN{std::unique_ptr<Node<pair_type>>(new Node<pair_type>(successor->data, DNP))}; // DN := the unique pointer to the newly created node which contains the successor's data
    //                 erase(successor->data.first);

    //                 DN->left.reset(locator->left.release()); // locator := the pointer to the node to be deleted
    //                 DN->left->parent = DN.get();
    //                 DN->right.reset(locator->right.release());
    //                 DN->right->parent = DN.get();

    //                 if (locator == DNP->left.get())
    //                 {
    //                     DNP->left.reset(DN.release());
    //                 }
    //                 else
    //                 {
    //                     DNP->right.reset(DN.release());
    //                 }
    //             }
    //             else
    //             {
    //                 successor->left.reset(locator->left.release());
    //                 successor->left->parent = successor;
    //                 erase(locator->data.first);
    //             }
    //         }
    //     }
    //     // std::cout <<"LOCATION OF LOCATOR "<< &locator<< "\n";
    // }

    // void erase(const key_type& x){
    //     auto it{find(x)}; //iterator to the node
    //     if (!(it.current)) {
    //         throw key_not_found("Couldn't find such a key in the tree");
    //     }
    //     node_type* tmp{it.current};
    //     if (tmp==head.get()) { //you have to delete the head
    //         if (!tmp->right && !tmp->left) { //no child
    //             head.reset();
    //         } else if( !(!tmp->left) != !(!tmp->right) ){ //one child
    //             if (tmp->left) {
    //                 head.reset(tmp->left.release());
    //                 tmp->left->parent = nullptr;
    //             } else {
    //                 head.reset(tmp->right.release());
    //                 tmp->right->parent = nullptr;
    //             }
    //         }else{ //two children
    //             auto in_order_succ{(++it).current};
    //             auto dumb = std::unique_ptr<node_type>( new node_type(in_order_succ->data,nullptr));
    //             dumb->left.reset(tmp->left.release());
    //             dumb->left->parent = dumb.get();
    //             if (in_order_succ==tmp->right.get()) {
    //                 dumb->right.reset(in_order_succ->right.release());
    //                 dumb->right->parent = dumb.get();
    //             } else {
    //                 dumb->right.reset(tmp->right.release());
    //                 dumb->right->parent = dumb.get();
    //                 if (in_order_succ->right) {
    //                     in_order_succ->right->parent = in_order_succ->parent;
    //                     in_order_succ->parent->left.reset(in_order_succ->right.release());
    //                 }else{
    //                     in_order_succ->parent->left.reset();
    //                 }
    //             }

    //             head.reset(dumb.release());

    //         }

    //     }else{ //the node to delete is not the head
    //         auto ptparent{tmp->parent}; //pointer to parent node
    //         if(!tmp->right && !tmp->left){ //no child case
    //             if(ptparent->left){
    //                 ptparent->left.reset();
    //             }else{
    //                 ptparent->right.reset();
    //             }
    //         }else if(!(!tmp->left) != !(!tmp->right)){ //one child case
    //             if(tmp->left){
    //                 tmp->left->parent = ptparent;

    //                 if(tmp == ptparent->left.get()){
    //                     ptparent->left.reset(tmp->left.release());
    //                 }else{
    //                     ptparent->right.reset(tmp->right.release());
    //                 }

    //             }else{
    //                 tmp->right->parent = ptparent;

    //                 if(tmp==ptparent->left.get()){
    //                     ptparent->left.reset(tmp->left.release());
    //                 }else{
    //                     ptparent->right.reset(tmp->right.release());
    //                 }

    //             }

    //         }else{ //two child case

    //             auto in_order_succ{(++it).current};
    //             auto dumb{std::unique_ptr<node_type>(new node_type(in_order_succ->data,ptparent))};
    //             dumb->left.reset(tmp->left.release());
    //             dumb->left->parent = dumb.get();
    //             if(in_order_succ==tmp->right.get()){ //successor is the right child of current node
    //                 if (!in_order_succ->right) { //if the successor has no right child
    //                     dumb->right.reset(); //set right child of dumb to nullptr
    //                 } else {//if the successor HAS right child
    //                     dumb->right.reset(in_order_succ->right.release());
    //                     dumb->right->parent = dumb.get();
    //                 }

    //                 if (ptparent->left.get()==tmp) {
    //                     ptparent->left.reset(dumb.release());
    //                 } else {
    //                     ptparent->right.reset(dumb.release());
    //                 }
    //             }else{
    //                 dumb->right.reset(tmp->right.release());
    //                 dumb->right->parent = dumb.get();
    //                 if (ptparent->left.get()==tmp) {
    //                     ptparent->left.reset(dumb.release());
    //                 } else {
    //                     ptparent->right.reset(dumb.release());
    //                 }

    //                 if(in_order_succ->right){
    //                     in_order_succ->right->parent = in_order_succ->parent;
    //                     in_order_succ->parent->left.reset(in_order_succ->right.release());
    //                 }else{ //no right child for inorder succ
    //                     in_order_succ->parent->left.reset();
    //                 }

    //             }

    //         }

    //     }

    // }

    /**
     * @brief Returns a reference to the value that is mapped to a key equivalent to x, performing an insertion if such key does not already exist.
     * @param x constant l-value ref. to a key
     * @see insert()
     */

    value_type &operator[](const key_type &x)
    {
        std::cout << "Calling l-value subscripting"
                  << "\n";
        /*auto insertion{insert(pair_type{x,value_type{}})}; //pair with an iterator to the node and a bool
         return insertion.first->second; //take the iterator and access the value
         */
        /*std::cout <<"Calling l-value subscripting" <<"\n";
        auto isfound = find_helper(x);
        if (isfound) {
            return isfound->data.second;
        } else { //key not found in tree
            return insert(pair_type{x,value_type{}}).first->second;
        }*/
        return subscript_helper(x);
    }

    /**
     * @brief Returns a reference to the value that is mapped to a key equivalent to x, performing an insertion if such key does not already exist. It's the r-valued version of `[]` operator
     * @param x r-value ref. to a key
     * @see insert()
     */

    value_type &operator[](key_type &&x)
    {
        // std::cout << "Calling move subscripting"
        //           << "\n";
        /*auto insertion{insert(pair_type{std::move(x),value_type{}})};
         return insertion.first->second;*/
        /*std::cout <<"Calling r-value subscripting" <<"\n";
        auto isfound = find_helper(std::move(x));
        if (isfound) {
            return isfound->data.second;
        } else { //key not found in tree
            return insert(pair_type{std::move(x),value_type{}}).first->second;
        }*/
        return subscript_helper(std::move(x));
    }

    /**
     * @brief Balance the tree by using the recursive (helper) function @ref balance_helper()
     * @see balance_helper()
     */

    void balance()
    {
        std::vector<pair_type> vec_nodes{};
        auto stop = end();
        for (auto it = begin(); it != stop; ++it)
        {
            vec_nodes.push_back(*it); //store the (ordered) nodes in a vector
        }
        clear();
        int middle{static_cast<int>((vec_nodes.size()) / 2)};
        this->insert(vec_nodes[middle]);
        balance_helper(vec_nodes, 0, middle - 1);
        balance_helper(vec_nodes, middle + 1, vec_nodes.size() - 1);
    }

    /**
     * @brief Prints the tree (given as `const reference` reference) traversed in order using the ++ operator.
     */
    friend std::ostream &operator<<(std::ostream &os, const bst &x)
    {

        auto endofTree = x.cend(); //tree is passed as constant
        for (auto it = x.cbegin(); it != endofTree; ++it)
        {
            os << it->first << " "; //os << (*it).first << " ";
        }
        return os;
    }

    /**
     * @brief Function that prints for each node: parent, left/right child and value. Used for visualize whether or not the tree is balanced.
     */
    void unordered_print()
    {
        auto endofTree = end(); //tree is passed as constant

        for (auto it = begin(); it != endofTree; ++it)
        {
            it.print_node_with_iterator();
            //            std::cout << "\n";
        }
    }

    /**
     * @brief Returns a boolean which is `True` if the tree is balanced, `False` otherwise.
     * @see balance_check()
     */

    bool is_balanced()
    {
        return balance_check(head.get());
    }

    /**
     * @brief Clear the tree by applying the method reset() to the head node.
     */

    void clear() noexcept
    {

        //        Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.
        //        If p is a null pointer (such as a default-initialized pointer), the unique_ptr becomes empty, managing no object after the call
        head.reset();
    }
};

#endif /* bst_h*/
