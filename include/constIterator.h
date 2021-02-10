#ifndef constIterator_h
#define constIterator_h

#include "Node.h"
#include <iterator>
#include <utility>

template <typename T >
struct const_iterator {
    using NodeT = Node<T>; //for the sake of readability
    
    /**
     * @brief Raw pointer to the current @ref Node
     */
    NodeT* current;
    
    //public:
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type *;
    
    /**
     * @brief Custom constructor for @ref iterator
     * @param pn Raw pointer to a @ref Node
     *
     * Construct a new @ref _iterator that refers to @ref Node pn
     */
    explicit _iterator(Node<T>* pn) noexcept: current{pn} {}
    
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
     * @brief Post- increment operator.
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
         * @brief Equality operator
         *
         * @param a Reference to first iterator.
         * @param b Reference to the second iterator
         * Two iterators are equal iff they point to the same @ref Node
         *
         */
        friend bool operator==(_iterator &a, _iterator &b) {
            return a.current == b.current;
        }
        
        /**
         *@brief Inequality operator
         *@param a Reference to the first iterator
         *@param b Reference to the second iterator
         *
         * To avoid code duplication, use the logical negation of `==` operator.
         */
        friend bool operator!=(_iterator &a, _iterator &b) { return !(a == b); }
      
    
    
    
    void print_node_with_iterator(){
        current->print();
    }
    };
    
#endif /* constIterator_h */






