#ifndef game_h
#define game_h 

#include <functional>
#include <assert.h>
#include <board_base.h>
#include <dice.h>

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

  enum event : int {
    
    ROLL_EVENT,
    SNAKE_LADDER_HIT_EVENT
  }; 

  void add_event_handler(const event ev, std::function<void(size_t)>&& cb) { _event_cb.at(ev) = std::move(cb); }

private:
  const board_base<T, C, R>& _board;
  const size_t _board_max_pos;
  dice<T, F> _d;

  size_t _pos{};
  bool _won; 
  
  std::array<std::function<void(size_t)>, 2> _event_cb{};
}; 


template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
void Game<T, C, R, F, goal_hit_exact>::roll() { 
  assert(!_won && "The game is already won, why would you still roll?!?!?");

  const size_t roll = _d.roll();
  const size_t new_pos = _pos + roll;

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
      _won = true;
  }
  else if(new_pos == _board_max_pos)
    _won = true; 
   
  _pos = new_pos;  
  if (_event_cb[ROLL_EVENT]) 
    _event_cb[ROLL_EVENT](roll);
}

#endif
