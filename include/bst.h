#ifndef bst_h
#define bst_h


#include "Iterator.h"
#include <functional> //std::less
#include <utility> //std::make_pair

template <typename key_type, typename value_type,typename cop = std::less<key_type> >
class bst{
    
    using pair_type = std::pair< const key_type, value_type>;
    using iterator = __iterator<pair_type>;
private:
    cop comp;
    std::unique_ptr<Node<pair_type>> head; //unique pointer to the root/head Node
    //I set the head to be a unique pointer so I can use release,get,reset member fcts
    
    /**
     * @brief Utility function that compares the keys between a pair and a pointer to a @ref Node<key_type, value_type>
     * @param x The std::pair used for the @ref insert function
     * @param ptr Raw pointer to a @ref Node
     */
    bool compare_keys(const pair_type& x, Node<pair_type>* ptr){
        if(comp(x.first,ptr->data.first)){
            return true;
        }else{
            return false;
        }
    }
    
public:
    /**
     * @brief Default constructor for the tree.
     */
    bst(): comp{}, head{nullptr}{}
    
    
    //TODO: copy/move semantics
        
    /**
     * @brief Returns an @ref Iterator to the first @ref Node, ordered by key
     */
    iterator begin(){
        
        if (!head) {
            return iterator{nullptr};
        }
        auto ptr{head.get()};
        while (ptr->left) {
            ptr=ptr->left.get();
        }
        return iterator{ptr};
    }
    
    
    /**
     * @brief const @ref Iterator to the first @ref Node, ordered by key
     */
    iterator begin() const{
        
        if (!head) {
            return iterator{nullptr};
        }
        auto ptr{head.get()};
        while (ptr->left) {
            ptr=ptr->left.get();
        }
        return iterator{ptr};
    }
    
    
    /**
     * @brief Iterator to the end of the tree
     */
    iterator end(){
        return iterator{nullptr};
    }
    
    /**
     * @brief const @ref Iterator to the end of the tree
     */
    iterator end() const{
        return iterator{nullptr};
    }
    
    /**
     *
     * @brief Insert a new @ref Node in the tree.
     * @param x Reference to a pair with a key and a value
     * Returns a std::pair with an @Iterator and a bool.
     */
    std::pair<iterator, bool> insert(const pair_type& x){
        auto ptr{head.get()};
        while (ptr) {
            if (compare_keys(x,ptr)) {
                if (ptr->left) {
                    ptr = ptr->left.get();
                }else{
                    ptr->left.reset(new Node<pair_type> {x,ptr});
                    return std::make_pair<iterator,bool>(iterator{ptr}, true);
                }
            }else if(!compare_keys(x,ptr)){
                if (ptr->right) {
                    ptr = ptr->right.get();
                } else {
                    ptr->right.reset(new Node<pair_type> {x,ptr});
                    return std::make_pair<iterator,bool>(iterator{ptr}, true);
                }
            }else{
                return std::make_pair<iterator,bool>(iterator{ptr}, false);
            }
        }
        head.reset( new Node<pair_type> {x,nullptr});
        return std::make_pair<iterator,bool>(iterator{head.get()}, true);
        //if you reached this point with no return call, then it must be that the tree is empy
    }
    
    
    
//    std::pair<iterator, bool> insert(pair_type&& x); //TODO: implement
    
    friend std::ostream& operator<<(std::ostream& os, const bst& x){
        
        auto endofTree = x.end();
        for (auto it=x.begin(); it!=endofTree; ++it) {
            os << it->first <<" "; //TODO: check if the fix in ++ is okay
        }
        return os;
    }
    
    

};


#endif /* bst_h*/
