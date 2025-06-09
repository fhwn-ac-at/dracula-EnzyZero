#include <atomic> 
#include <stop_token>
#include <random>
#include <future>

#include "../settings.h"
#include "common.h"
#include "snakes_ladders_board.h"
#include "statistic_containers.h"

using namespace settings;

void task(std::stop_token                         st, // supplied by jthread constructor
          const unsigned                          thread_id,
          std::atomic_int&                        global_runs_count,
          const int                               assigned_runs, 
          const int                               base_seed,
          const decltype(dice::weights)&          weights,
          const SnakesLaddersBoard<cmn::board_int_t, board::cols, board::rows>& board,
          std::promise<ThreadResult>               return_promise
      )
{ 
  // create a rand device
  std::mt19937 gen(base_seed + thread_id);
  std::discrete_distribution d(weights.cbegin(), weights.cend());
    
  ThreadResult result;

  // outer loop for each game
  for(int runs = 0; runs < assigned_runs && !st.stop_requested(); runs++, global_runs_count--) 
  { 
    GameStats game;

    // inner game loop for steps in a game
    for (
      int roll = d(gen), pos = 0; 
      assigned_runs > 0 && !st.stop_requested();
      roll = d(gen)
    )
    {
      
    }

    // save game stats if new minimum
    if (game < result.shortest_game)
      result.shortest_game = std::move(game);
  }
  
  
  
}
