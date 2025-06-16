#ifndef event_base_h
#define event_base_h

#include <assert.h>
#include <array>
#include <functional>
#include <concepts>
#include <tuple>

template <std::size_t E, typename Ret, typename ...Args>
class event_base {
public:

  using return_t = Ret;
  using args_tuple_t = std::tuple<Args...>;
  static constexpr size_t event_num = E;

  template <typename H>
  requires (std::is_invocable_r_v<Ret, H, Args> || ...)
  void subscribe(const unsigned event_id, H&& handler) {
    assert(_valid_event_id(event_id) && "Invalid event id");

    _listeners[event_id] = handler;
  }

  void unsubscribe(const unsigned event_id) {

    assert(_valid_event_id(event_id) && "Invalid event id");
    _listeners[event_id] = {};
  }

  template<typename Arg, bool check_if_subscribed = true> 
  requires (std::same_as<std::decay_t<Arg>, Args> || ...)
  void publish(const unsigned event_id, Arg&& arg) {
    assert(_valid_event_id(event_id) && "Invalid event id");
  
    // check if something is subscribed, otherwise just call
    if constexpr (check_if_subscribed)
    {
      if (auto& target = _listeners[event_id]; !!target)
        target(std::forward<Arg>(arg));
    }
    else 
    {
      target(std::forward<Arg>(arg));
    }
  }

private: 
  std::array<std::function<Ret(Args...)>, E> _listeners;
 
  static constexpr bool _valid_event_id(const unsigned id) { return id >= 0 && id < E; }  
};

#endif
