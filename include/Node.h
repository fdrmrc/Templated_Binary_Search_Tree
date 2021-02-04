#ifndef Node_h
#define Node_h


#include <iostream>
#include <memory>

template <typename T>
struct Node{
    /** @brief Data to be stored in the Node*/
    T data;
    /** @brief Unique pointer to the left child*/
    std::unique_ptr<Node<T>> left;
    
    /** @brief Unique pointer to the right child*/
    std::unique_ptr<Node<T>> right;
    
    /**@brief Raw pointer to the parent @ref Node*/
    Node<T>* parent;
    
    /**
     @brief Custom constructor
    */
  
    explicit Node(const T& _data): data{_data}, left{nullptr}, right{nullptr},parent{nullptr}{}

    /**
     @brief Default constructor
     */
    Node(): data{},left{nullptr}, right{nullptr},parent{nullptr}{}
    
    /**
     * @brief Default destructor
     */
    
//    ~Node(){
////        std::cout << "def destr"<<std::endl;
//        if(parent){
//            delete[] parent;
//        }
//    };
    
    /**
     @brief Copy constructor
     */
    
    Node(const T& _data, Node<T>* _parent) noexcept:
        data{_data},
        left{nullptr},
        right{nullptr},
        parent{_parent} {}

    Node(const std::unique_ptr<Node<T>>& ptn, Node<T>* _parent): data{ptn->data}{
        parent = _parent;
        if(ptn->right){
            right = std::make_unique<Node<T>>(ptn->right, this);
        }
        if(ptn->left){
            left = std::make_unique<Node<T>>(ptn->left, this);
        }
    }
    
    /**
     @brief Move constructor
     */
    
    Node(const T&& _data, Node<T>* _parent) noexcept:
        data{std::move(_data)},
        left{nullptr},
        right{nullptr},
        parent{_parent} {}
    
    
    /**
     @brief Simple void function that prints a @ref Node. Used just for testing.
     */
    
    void print(){
//        std::cout <<"Node has value: " << data.second <<"\n";
//        if (left) {
//            std::cout << "Left child has value: " <<left->data.second <<"\n";
//        }if(right){
//            std::cout << "Right child has value: " << right->data.second << "\n";
//        }if(parent){
//            std::cout << "Parent is Node with value: " <<parent->data.second <<"\n";
//        }
        
    }
    
    
    
};


#endif /* Node_h */
