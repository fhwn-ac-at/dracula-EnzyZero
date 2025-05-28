#ifndef stack_h
#define stack_h

#include <vector>

/**
 * @brief Simple stack using a Vector
 *   
 * Mind that the back of the vector is used as the top of the stack.
 */
template <typename T>
class Stack {
public: 

    using value_type = T;

    T& peek()             { return vector_.back(); }
    void push(auto&& val) { vector_.emplace_back( val ); }
    T pop()               { return *vector_.erase( vector_.end() - 1 ); }

    template <typename... Args>
    void emplace(Args&&... args) { vector_.emplace_back( std::forward<Args>(args)... ); }

    bool empty()    { return vector_.empty(); }
    operator bool() { return !empty(); }

    std::vector<T>::reverse_iterator begin() { return vector_.rbegin(); }
    std::vector<T>::reverse_iterator end()   { return vector_.rend(); }

private:  
    std::vector<T> vector_;
};

#endif