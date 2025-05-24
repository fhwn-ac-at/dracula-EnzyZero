#ifndef stack_h
#define stack_h

#include <vector>

template <typename T>
class Stack {
public:

    T& peek() { return vector_.back(); }
    void push(T&& val) { vector_.emplace_back( val ); }
    T pop() { return *vector_.erase( vector_.end() - 1 ); }

    template <typename... Args>
    void emplace(Args&&... args) { vector_.emplace_back( std::forward<Args>(args)... ); }

    bool empty() { return vector_.empty(); }
    operator bool() { return !empty(); }

    std::vector<T>::iterator begin() { return vector_.begin(); }
    std::vector<T>::iterator end() { return vector_.end(); }

private:  
    std::vector<T> vector_;
};

#endif