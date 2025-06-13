#ifndef game_h
#define game_h 

#include <functional>
#include <assert.h>
#include <board_base.h>
#include <dice.h>
#include <variant>

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact = false> 
class Game {
public: 

  constexpr Game(const board_base<T, C, R>& board, dice<T, F>&& d)
  : _board( board ), _board_max_pos( board.max_field_pos() ), _d( std::move(d) ), _won( false )
  { 
    assert(_board.valid() && "Board is invalid");
  }

  void roll();

  bool won() const { return _won; }
  operator bool() const { return won(); } 

  void reset() { _won = false; _pos = 0; } 

  using event_arg_t = std::variant<size_t, unsigned, std::monostate>;
 
  static constexpr int events = 2; 
  enum event : int {
    
    ROLL_EVENT,             // unsigned
    SNAKE_LADDER_HIT_EVENT, // size_t 
    WON_EVENT               // monostate
  }; 

  void add_event_handler(const event ev, std::function<void(event_arg_t)>&& cb) { _event_cb.at(ev) = std::move(cb); }

private:
  const board_base<T, C, R>& _board;
  const size_t _board_max_pos;
  dice<T, F> _d;

  size_t _pos{};
  bool _won; 
  
  std::array<std::function<void(event_arg_t)>, events> _event_cb{};

  template<typename CB>
  std::function<void(event_arg_t)> _wrap_handler(CB&& cb) {  

    // hack i got from chatGPT
    return [f = std::forward<F>(cb)](event_arg_t arg) { 

      std::visit([&](auto&& val) {
        using Arg = std::decay_t<decltype(val)>; 

        // Only call if the function is invocable with this type
        if constexpr (std::is_invocable_v<CB, Arg>) {
          f(val);
        }
      }, arg); // std::visit
    };
  } 

}; 


template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
void Game<T, C, R, F, goal_hit_exact>::roll() { 
  assert(!_won && "The game is already won, why would you still roll?!?!?");

  const unsigned roll = _d.roll();
  const size_t new_pos = _pos + roll;

  if (_event_cb[ROLL_EVENT]) 
    _event_cb[ROLL_EVENT](roll); 

  if (new_pos <= _board_max_pos)
  {
    new_pos += _board[new_pos]; // jumps happen here 
    if (_event_cb[SNAKE_LADDER_HIT_EVENT]) 
      _event_cb[SNAKE_LADDER_HIT_EVENT](_board[new_pos]);
  }

  // overshoot is not a win if goal_hit_exact is true
  if (_pos > new_pos)
  {
    if constexpr (goal_hit_exact)
      return; // rollback

    else
     goto won;
  }
  else if(new_pos == _board_max_pos)
     goto won;
   
  _pos = new_pos;
  return; 

won:
  _won = true;
  if (_event_cb[WON_EVENT]) 
    _event_cb[WON_EVENT]();
}

#endif
