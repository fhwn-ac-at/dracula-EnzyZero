#ifndef event_base_h
#define event_base_h

#include <assert.h>
#include <array>
#include <functional>
#include <variant>
#include <concepts>

template <std::size_t E, typename ...T>
class event_base {
public:

  template <typename H>
  requires (std::is_invocable_r_v<void, H, T> || ...)
  void subscribe(const int event_id, H&& handler) {
    static_assert(_valid_event_id(event_id), "Invalid event id");

    _listeners[event_id] = [h = std::forward<H>(handler)](handler_arg_t arg) {
      std::visit([&](auto&& val) {
        static_assert(std::is_invocable_r_v<void, decltype(h), std::decay_t<decltype(val)>>,
        "Handler must return void and be callable with arg passed");
        h(val);
      }, arg);
    };
  }

  void unsubscribe(const int event_id);

  template<typename Arg>
  requires (std::same_as<std::decay_t<Arg>, T> || ...)
  void publish(const int event_id, Arg&& arg) {
    static_assert(_valid_event_id(event_id), "Invalid event id");

    if (auto& target = _listeners[event_id]; !!target)
      target(std::forward<Arg>(arg));
  }

private: 
  using handler_arg_t = typename std::variant<T...>;

  std::array<std::function<void(handler_arg_t)>, E> _listeners;
 
  static constexpr bool _valid_event_id(const int id) { 
    return id >= 0 && id < E;
  }  
};

/*
template <std::size_t E, typename ...T>
template <typename H>
requires (std::is_invocable_r_v<void, H, T> || ...)
void event_base<E, T...>::subscribe(const int event_id, H&& handler) {
  static_assert(_valid_event_id(event_id), "Invalid event id");

  _listeners[event_id] = [h = std::forward<H>(handler)](handler_arg_t arg) {
    std::visit([&](auto&& val) {
      static_assert(std::is_invocable_r_v<void, decltype(h), std::decay_t<decltype(val)>>,
                    "Handler must return void and be callable with arg passed");
      h(val);
    }, arg);
  };
}

template <std::size_t E, typename... T>
template <typename Arg>
requires (std::same_as<std::decay_t<Arg>, T> || ...)
void event_base<E, T...>::publish(const int event_id, Arg&& arg) {
  static_assert(_valid_event_id(event_id), "Invalid event id");

  if (auto& target = _listeners[event_id]; !!target)
    target(std::forward<Arg>(arg));
}


*/

template <std::size_t E, typename... T>
void event_base<E, T...>::unsubscribe(const int event_id) {
  static_assert(_valid_event_id(event_id), "Invalid event id");
  _listeners[event_id] = {};
}

#endif
