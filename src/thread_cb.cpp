#include <assert.h>
#include <vector>
#include <atomic> 
#include <stop_token>
#include <random>
#include <future>
#include <numeric>

#include "../settings.h"
#include "common.h"
#include "board.h"
#include "statistic_containers.h"

using namespace settings;

void task(std::stop_token                          st, // supplied by jthread constructor
          std::atomic_int&                         global_runs_count,
          const int                                assigned_runs, 
          const int                                mixed_seed,
          const decltype(settings::dice::weights)& weights,
          const Board<cmn::board_int_t, 
            board::cols, board::rows>&             board,
          std::promise<ThreadResult>               promise
      )
{
  assert(board && assigned_runs >= 0 && "Board is invalid"); 

  // create a rand device
  std::mt19937 gen(mixed_seed);
  std::discrete_distribution d(weights.cbegin(), weights.cend()); 

  ThreadResult result;
  GameStats game;  

  std::vector<double> avrg_game_rolls;
  avrg_game_rolls.reserve(assigned_runs);

  // outer loop for each game
  for(int runs = 0; runs < assigned_runs && !st.stop_requested(); runs++, global_runs_count--) 
  { 
    // inner game loop for steps in a game
    for (int roll = d(gen), pos = 0, last_pos = 0; !st.stop_requested(); roll = d(gen))
    {
      game.rolls++;
      game.roll_sequence.push_back(roll);  

      // if overshoots are not allowed, save last position
      if constexpr (settings::board::goal_hit_exact)
        last_pos = pos;

      // set new position
      if (unsigned field = board[pos]; field != 0)
      {
        pos += field;
        result.snakes_ladders_hits.at(field)++; 
      } 
      else
        pos++;

      // decide between the two win-strategies
      if constexpr (settings::board::goal_hit_exact) 
      {
        if (static_cast<size_t>(pos) == board.max_field_pos()) 
          break;
        else
          pos = last_pos;
      }
      else 
      {
        if (static_cast<size_t>(pos) >= board.max_field_pos())
          break;
      }
    }
    
    // save avrg rolls of a game
    const double avrg = std::accumulate(game.roll_sequence.begin(), game.roll_sequence.end(), 0) / static_cast<double>(game.rolls); 
    avrg_game_rolls.push_back(avrg);

    // save game stats if new minimum found
    if (game < result.shortest_game)
    {
      result.shortest_game = std::move(game);
      game.roll_sequence.reserve(avrg);
    }

    game.reset();
  }

  if (!st.stop_requested())
    return;

  // calculate the average rolls of all games 
  const double avrg = std::accumulate(avrg_game_rolls.begin(), avrg_game_rolls.end(), 0) / static_cast<double>(assigned_runs); 
  result.avrg_rolls = avrg; 
  
  promise.set_value(std::move(result));
}
