#ifndef Iterator_h
#define Iterator_h

#include "Node.h"
#include <iterator>
#include <utility>

template <typename T, bool is_const=true >
struct _iterator {
    using nodeT = Node<T>; //for the sake of readability. T will be pair_type
    
    /**
     * @brief Raw pointer to the current @ref Node
     */
    nodeT* current;
    
    
    using value_type = typename std::conditional<is_const, const T, T>::type;
    using reference = typename std::conditional<is_const, const T&, T&>::type;
    using pointer = typename std::conditional<is_const, const T*, T*>::type;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    
    /**
     * @brief Custom constructor for @ref iterator
     * @param pn Raw pointer to a @ref Node
     *
     * Construct a new @ref _iterator that refers to @ref Node pn
     */
    explicit _iterator(nodeT* pn) noexcept: current{pn} {}
    
    /**
     * @brief Default-generated constructor
     *
     */
    _iterator() noexcept=default;
    
    /**
     * @brief Default-generated destructor
     *
     */
    ~_iterator()=default;
    
    
    /**
     * @brief Dereference operator
     *
     * Dereferences an @ref _iterator by returning the data stored by the @ref Node it refers to
     */
    reference operator*() const noexcept{
        return current->data; //I will always feed a std::pair
    }
    
    
    /**
     * @brief Arrow operator
     *
     * Access operator: it return a pointer to the data stored in the @ref Node the @ref _iterator refers to
     */
    pointer operator->() const noexcept{
        return &**this;
    }
    
    
    /**
     * @brief Pre-increment operator.
     * It's marked noexecpt as we're not acquiring any resource and nothing can go wrong.
     */
    _iterator& operator++() noexcept {
        
        
        /* Less tricky version */
        if (!current) {
            return *this;
        } else if(!current->right){ //no right child
            
            while (current->parent && current==current->parent->right.get()) {
                current = current->parent;
            }
            current = current->parent;
            
        }else if(current->right){ //has right child
            current = current->right.get(); //go right
            while (current->left) { //keep descending on the left subtree to find the next value
                current=current->left.get();
            }
        }
        
        return  *this;
    }
    
    
    /**
     * Post-increment
     */
    _iterator operator++(int) {
      auto tmp{*this};
      ++(*this);
      return tmp;
    }
    /**
     * @brief Equality operator
     *
     * @param candidate Reference to the iterator we want to compare.
     * Two iterators are equal iff they point to the same @ref Node
     *
     */
    //        template <bool B>
    //        friend bool operator==(_iterator&a, _iterator &b) { //old version
    //            return a.current == b.current;
    //        }
    
    template<bool constBool>
    bool operator==(const _iterator<T,constBool>& candidate) const noexcept
    {
        return current == candidate.current;
    }
    /**
     *@brief Inequality operator
     *@param candidate Reference to the iterator we want to compare.
     *
     * To avoid code duplication, use the logical negation of `==` operator.
     */
    template<bool constBool>
    bool operator!=(const _iterator<T,constBool>& candidate) const noexcept { return !(current == candidate.current); }
    
    
    
    
    void print_node_with_iterator(){
        current->print();
    }
};

#endif /* Iterator_h */






