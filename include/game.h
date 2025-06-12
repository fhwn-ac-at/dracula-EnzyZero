#ifndef game_h
#define game_h 

#include <assert.h>
#include <vector>
#include <board_base.h>
#include <dice.h>

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact = false> 
class Game {
public:
  
  Game(const board_base<T, C, R>& board, dice<T, F>&& d, const unsigned reserve = 100)
  : _board( board ), _d( std::move(d) ), _won( false )
  { 
    assert(_board.valid() && "Board is invalid");
    _roll_sequence.reserve(reserve);
  }

  void roll();

  constexpr bool won() const { return _won; }
  constexpr operator bool() const { return won(); } 

private:
  const board_base<T, C, R>& _board;
  dice<T, F> _d;

  size_t _pos{};
  std::vector<T> _roll_sequence; 

  bool _won;
}; 



template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact> 
constexpr void Game<T, C, R, F, goal_hit_exact>::roll() { 
  assert(!_won && "The game is already won, why would you still roll?!?!?");

  const size_t roll = _d.roll();
  _pos += roll; 

  // overshoot is not a win if goal_hit_exact is true
  if (_pos > _board.max_field_pos())
  {
    if constexpr (goal_hit_exact)
    {
      _pos = _roll_sequence.back();
      return;
    }
    else
    _won = true;
  }
  else if(_pos == _board.max_field_pos())
    _won = true;

  _roll_sequence.push_back(roll);
}

#endif
