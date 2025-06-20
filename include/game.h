#ifndef game_h
#define game_h 

#include <functional>
#include <assert.h>
#include <board_base.h>
#include <dice.h>
#include <memory>
#include <variant>
#include <spdlog/logger.h>
#include <spdlog/sinks/null_sink.h>

template <typename Cb>
concept EventCallback =
  std::invocable<Cb, unsigned> ||
  std::invocable<Cb, size_t> ||
  std::invocable<Cb>; 

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact = false> 
class Game {
public:

  Game(const board_base<T, C, R>& board, Dice<T, F>&& d, std::shared_ptr<spdlog::logger> logger =
         std::make_shared<spdlog::logger>("", std::make_shared<spdlog::sinks::null_sink_mt>()))

  : _board( board ), _board_max_pos( board.max_field_pos() ), _d( std::move(d) ), _won( false ), _logger( std::move(logger) )
  { 
    assert(_board.valid() && "Board is invalid");
  }

  void roll();

  bool won() const { return _won; }
  operator bool() const { return won(); } 

  void reset() { _won = false; _pos = 0; _logger->debug("Game reset"); } 

  static constexpr int events = 3; 
  enum event : int {
    
    ROLL_EVENT,             // unsigned
    SNAKE_LADDER_HIT_EVENT, // size_t 
    WON_EVENT               // monostate
  }; 

  template <EventCallback Cb>
  void add_event_handler(const event ev, Cb&& cb) { _event_cb.at(ev) = _wrap_handler(std::move(cb)); }

private:
  const board_base<T, C, R>& _board;
  const size_t _board_max_pos;
  Dice<T, F> _d;

  size_t _pos{};
  bool _won;
  std::shared_ptr<spdlog::logger> _logger;
  
  using _event_arg_t = std::variant<size_t, unsigned, std::monostate>;
  std::array<std::function<void(_event_arg_t)>, events> _event_cb{};

  template<EventCallback Cb>
  std::function<void(_event_arg_t)> _wrap_handler(Cb&& cb); 
}; 


template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
void Game<T, C, R, F, goal_hit_exact>::roll() { 
  assert(!_won && "The game is already won, why would you still roll?!?!?");

  const unsigned roll = _d.roll(); 
  _logger->trace("Game roll: {}", roll);

  size_t new_pos = _pos + roll;
 
  // fire roll_event here
  if (_event_cb[ROLL_EVENT])
  {
    _logger->trace("Game firing ROLL_EVENT");
    _event_cb[ROLL_EVENT](roll); 
  }

  if (new_pos <= _board_max_pos)
  {
    new_pos += _board[new_pos]; // jumps happen her

    // fire SNAKE_LADDER_HIT_EVENT
    if (_board[new_pos] && _event_cb[SNAKE_LADDER_HIT_EVENT])
    {
      _logger->trace("Game firing SNAKE_LADDER_HIT_EVENT");
      _event_cb[SNAKE_LADDER_HIT_EVENT](_board[new_pos]);
    }
  }

  // overshoot is not a win if goal_hit_exact is true
  if (new_pos > _board_max_pos)
  {
    if constexpr (goal_hit_exact)
      return; // rollback

    else
     goto won;
  }
  else if(new_pos == _board_max_pos)
     goto won;
  
  // assign new position
  _pos = new_pos;
  _logger->trace("Game pos: {}", _pos);
  return; 

won:
  _won = true;

  // fire WON_EVENT
  if (_event_cb[WON_EVENT])
  {
    _logger->trace("Game firing WON_EVENT");
    _event_cb[WON_EVENT]({});
  }

  _logger->debug("Game won");
} 

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
template <EventCallback Cb>
auto Game<T, C, R, F, goal_hit_exact>::_wrap_handler(Cb&& cb) -> std::function<void(typename Game<T, C, R, F, goal_hit_exact>::_event_arg_t)> {

  // hack i got from chatGPT
  return [f = std::forward<Cb>(cb)](_event_arg_t arg) { 

    std::visit([&](auto&& val) {
      using Arg = std::decay_t<decltype(val)>; 

      // Only call if the function is invocable with this type
      if constexpr (std::is_invocable_v<Cb, Arg>)
        f(val);

    }, arg); // std::visit
  }; // lambda
} 

#endif
