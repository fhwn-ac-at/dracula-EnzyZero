#ifndef stack_h
#define stack_h

#include <vector>

template <typename T>
class stack {
public:

    T& peek() { return vector_.back(); }
    void push(T&& val) { vector_.emplace_back( val ); }
    T pop() { return *vector_.erase( vector_.end() - 1 ); }

    template <typename... Args>
    void emplace(Args&&... args) { vector_.emplace_back( std::forward<Args>(args)... ); }

    bool empty() { return vector_.empty(); }
    operator bool() { return !empty(); }

    std::vector<T>::reverse_iterator begin() { return vector_.rbegin(); }
    std::vector<T>::reverse_iterator end() { return vector_.rend(); }

private:  
    std::vector<T> vector_;
};

#endif