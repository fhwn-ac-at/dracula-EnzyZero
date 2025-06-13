#include <assert.h>
#include <atomic> 
#include <stop_token>
#include <future>

#include "board_base.h"
#include "statisics.h"
#include "dice.h"
#include "game.h"

template <typename T, size_t C, size_t R, size_t F>
void task(std::stop_token              st, // supplied by jthread constructor
          std::atomic_int&             global_runs_count,
          const int                    assigned_runs, 
          const size_t                 mixed_seed,
          const std::span<T>           weights_list,
          const board_base<T, C, R>&   board,

          StatisticsCollector&&        mcollector,
          std::promise<Statistics>     promise
      )
{
  assert(board && assigned_runs >= 0 && "Board is invalid");  

  using Game = Game<T, C, R, F>;

  Dice dice(mixed_seed, weights_list);
  Game game(board, std::move(dice));
  StatisticsCollector collector = std::move(mcollector);
   
  // add collector methods as
  game.add_event_handler(Game::ROLL_EVENT, std::bind(&StatisticsCollector::add_roll, &collector, std::placeholders::_1)); 
  game.add_event_handler(Game::SNAKE_LADDER_HIT_EVENT, std::bind(&StatisticsCollector::add_snake_ladder_hit, &collector, std::placeholders::_1)); 
  game.add_event_handler(Game::WON_EVENT, std::bind(&StatisticsCollector::finalize, &collector)); 
 
  // the game-loop
  for(int runs = 0; runs < assigned_runs && !st.stop_requested(); runs++, global_runs_count--) 
  { 
    // inner game loop for steps in a game
    while (!st.stop_requested() && !game.won())
      game.roll();
    
    game.reset();
  }

  if (!st.stop_requested())
    return;

  promise.set_value(collector.get_results());
}
