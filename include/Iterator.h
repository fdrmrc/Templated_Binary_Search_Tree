#ifndef Iterator_h
#define Iterator_h

#include "Node.h"
#include <iterator>
#include <utility>

template <typename T >
struct __iterator {
    using NodeT = Node<T>; //for the sake of readability
    
    /**
     * @brief Raw pointer to the current @ref Node
     */
    NodeT* current;
    
    //public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type *;
    
    /**
     * @brief Custom constructor for @ref __iterator
     * @param pn Raw pointer to a @ref Node
     *
     * Construct a new @ref __iterator that refers to @ref Node pn
     */
    explicit __iterator(NodeT* pn) : current{pn} {}
    
    /**
     * @brief Default-generated constructor
     *
     */
    __iterator() noexcept=default;
    
    /**
     * @brief Default-generated destructor
     *
     */
    ~__iterator()=default;
    
    
    /**
     * @brief Dereference operator
     *
     * Dereferences an @ref __iterator by returning the data stored by the @ref Node it refers to
     */
    reference operator*() const noexcept{
        return current->data; //I will always feed a std::pair
    }
    
    
    /**
     * @brief Arrow operator
     *
     * Access operator: it return a pointer to the data stored in the @ref Node the @ref __iterator refers to
     */
    pointer operator->() const noexcept{
        return &**this;
    }
    
    
    /**
     * @brief Post- increment operator.
     * It's marked noexecpt as we're not acquiring any resource and nothing can go wrong.
     */
    __iterator& operator++() noexcept {
        
        
        /* Shorter and less tricky */
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
         * @brief Equality operator
         *
         * @param a Reference to first iterator.
         * @param b Reference to the second iterator
         * Two iterators are equal iff they point to the same @ref Node
         *
         */
        friend bool operator==(__iterator &a, __iterator &b) {
            return a.current == b.current;
        }
        
        /**
         *@brief Inequality operator
         *@param a Reference to the first iterator
         *@param b Reference to the second iterator
         *
         * Logical negation of `==` operator
         */
        friend bool operator!=(__iterator &a, __iterator &b) { return !(a == b); }
        
    };
    
#endif /* Iterator_h */
