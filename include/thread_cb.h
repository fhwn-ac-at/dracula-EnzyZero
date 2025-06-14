#ifndef thread_cb_h
#define thread_cb_h

#include <assert.h>
#include <atomic> 
#include <stop_token>
#include <future>
#include <spdlog/logger.h>
#include <unistd.h>
#include <ranges>

#include "board_base.h"
#include "statistics.h"
#include "dice.h"
#include "game.h"

template <typename T, unsigned C, unsigned R, unsigned F, std::ranges::input_range r>
void task(std::stop_token                  st, // supplied by jthread constructor
          std::shared_ptr<spdlog::logger>  logger,
          std::atomic_int&                 global_runs_count,
          const int                        assigned_runs, 
          const size_t                     mixed_seed,
          r&&                              weights_list,
          const board_base<T, C, R>&       board,

          StatisticsCollector<T>           collector,
          std::promise<Statistics<T>>      promise
      )
{

  assert(board && assigned_runs >= 0 && "Board is invalid"); 

  const int thread_id = gettid();
  logger->info("Thread [{}]: running {} games with mixed_seed {}", thread_id, assigned_runs, mixed_seed);

  using Dice = Dice<T, F>;
  using Game = Game<T, C, R, F>;

  Dice dice(weights_list, mixed_seed);
  Game game(board, std::move(dice), logger);
   
  // add collector methods as
  game.add_event_handler(Game::ROLL_EVENT,             std::bind(&StatisticsCollector<T>::add_roll,             &collector, std::placeholders::_1));
  game.add_event_handler(Game::SNAKE_LADDER_HIT_EVENT, std::bind(&StatisticsCollector<T>::add_snake_ladder_hit, &collector, std::placeholders::_1));
  game.add_event_handler(Game::WON_EVENT,              std::bind(&StatisticsCollector<T>::finalize,             &collector)); 
 
  // the game-loop
  for(int runs = 0; runs < assigned_runs && !st.stop_requested(); runs++, global_runs_count--) 
  {
    logger->trace("Thread [{}]: outer loop index {}", thread_id, runs);

    // inner game loop for steps in a game
    while (!st.stop_requested() && !game.won())
      game.roll();

    logger->trace("Thread [{}]: game finished, resetting game", thread_id);
    game.reset();
  }

  if (!st.stop_requested())
  {
    logger->info("Thread [{}] stopped", thread_id);
    return;
  }

  logger->debug("Thread [{}] finished", thread_id);
  promise.set_value(collector.get_results());
}

#endif
