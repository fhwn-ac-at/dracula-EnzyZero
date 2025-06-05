#ifndef coroutine_h
#define coroutine_h

// ideas from https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

#include <utility>
#include <coroutine>

/**
 * @brief Minimal setup to get a c++ coroutine working
 * It does not return anything (void) and manages the coroutine_handle. 
 * The nested promise_type is necessary for the compiler.
 */
struct Coroutine {

    struct promise_type { 
        using Handle = std::coroutine_handle<promise_type>;

        Coroutine get_return_object() {
            return Coroutine{Handle::from_promise(*this)};
        }

        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }

        void return_void() {}
        void unhandled_exception() {}
    };

    Coroutine(promise_type::Handle coro_handle)
    :   coro_(coro_handle)
    {}

    // copies are deleted
    Coroutine(Coroutine& other) = delete;
    Coroutine& operator=(Coroutine& other) = delete;

    // move is allowed
    Coroutine(Coroutine&& other) noexcept
    :   coro_( std::exchange(other.coro_, {}) ) {}

    Coroutine& operator=(Coroutine&& other) noexcept;

    /**
     * @brief Check if the coroutine exists/is done
     * 
     * @return true 
     * @return false 
     */
    operator bool() { return !!coro_; }
    bool done() { return coro_.done(); }

    /**
     * @brief resume the coroutine
     * 
     * Check if the coro is valid appropriately.
     */
    void resume() { coro_.resume(); }
    void operator()() { resume(); }

    ~Coroutine() { if (coro_) coro_.destroy(); }

private: 
    promise_type::Handle coro_;
};

inline Coroutine& Coroutine::operator=(Coroutine&& other) noexcept { 

    if (this == &other) return *this;
    if (coro_) 
        coro_.destroy(); 

    coro_ = std::exchange(other.coro_, {});
    return *this;
}

#endif