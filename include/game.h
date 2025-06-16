#ifndef game_h
#define game_h 

#include <assert.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/null_sink.h>

#include "dice.h"
#include "board_base.h"
#include "game_event.h"

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact = false> 
class Game {
public: 
  
  GameEvent event;
  using enum GameEvent::events;

  Game(
    const board_base<T, C, R>& board, 
    Dice<T, F>&& d, 
    std::shared_ptr<spdlog::logger> logger = nullptr // optional logger
  );

  void roll();

  bool won() const { return _won; }
  operator bool() const { return won(); } 

  void reset() { _won = false; _pos = 0; _logger->debug("Game reset"); } 

private:
  const board_base<T, C, R>& _board;
  const size_t _board_max_pos;
  Dice<T, F> _d;

  size_t _pos{};
  bool _won;
  std::shared_ptr<spdlog::logger> _logger;
}; 


template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
Game<T, C, R, F, goal_hit_exact>::Game(const board_base<T, C, R>& board, Dice<T, F>&& d, std::shared_ptr<spdlog::logger> logger)
  : _board( board ), 
  _board_max_pos( board.max_field_pos() ), 
  _d( std::move(d) ), 
  _won( false ), 
  _logger( logger ? std::move(logger) : std::make_shared<spdlog::logger>("", std::make_shared<spdlog::sinks::null_sink_mt>()) )
{ 
  assert(_board.valid() && "Board is invalid");
}

template <std::integral T, size_t C, size_t R, size_t F, bool goal_hit_exact>
void Game<T, C, R, F, goal_hit_exact>::roll() { 
  assert(!_won && "The game is already won, why would you still roll?!?!?");
 
  // roll but do not overwrite current pos
  const size_t roll = _d.roll(); 
  size_t new_pos = _pos + roll; 
  _logger->trace("Game roll: {}", roll);
  event.publish(ROLL_EVENT, roll);

  // jumps happen here
  if (const size_t jump = _board[new_pos]; new_pos <= _board_max_pos && jump != 0)
  {
    new_pos += jump; 
    event.publish(SNAKE_LADDER_HIT_EVENT, jump);
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
  event.publish(POS_EVENT, _pos);
  _logger->trace("Game pos: {}", _pos);
  return; 

won:
  _won = true;

  // fire WON_EVENT
  event.publish(WON_EVENT, 0ul);
  _logger->debug("Game won");
} 

#endif
