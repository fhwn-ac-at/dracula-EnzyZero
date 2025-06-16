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

template <typename T, unsigned C, unsigned R, unsigned F, std::ranges::input_range _R>
void task(std::stop_token                  st, // supplied by jthread constructor
          std::shared_ptr<spdlog::logger>  logger,
          std::atomic_size_t&              global_runs_count,
          const int                        assigned_runs, 
          const size_t                     mixed_seed,
          _R&&                             weights_list,
          const board_base<T, C, R>&       board,

          StatisticsCollector              collector,
          std::promise<Statistics>         promise
      )
{
  assert(board && assigned_runs >= 0 && "Board is invalid");
  const int thread_id = gettid();

  using Dice = Dice<T, F>;
  using Game = Game<T, C, R, F>;

  Dice dice(weights_list, mixed_seed);
  Game game(board, std::move(dice), logger);
   
  // add collector methods as
  game.event.subscribe(Game::ROLL_EVENT,             [&collector](const size_t r) { collector.add_roll(r); });
  game.event.subscribe(Game::SNAKE_LADDER_HIT_EVENT, [&collector](const size_t h) { collector.add_snake_ladder_hit(h); });
  game.event.subscribe(Game::WON_EVENT,              [&collector]([[maybe_unused]] const size_t n) {collector.finalize(); });
 
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

  if (st.stop_requested())
    logger->debug("Thread [{}] stopped", thread_id);
  else 
    logger->debug("Thread [{}] finished normally", thread_id);

  promise.set_value(collector.get_results());
}

#endif
