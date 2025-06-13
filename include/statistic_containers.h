#ifndef statistic_containers_h
#define statistic_containers_h

#include <vector>
#include <unordered_map>
#include <compare> 

#include "snakes_ladders_list.h"
#include "../settings.h" 

struct Game {

  unsigned rolls{};
  std::vector<int> roll_sequence; 

  void reset() { rolls = 0; roll_sequence.clear(); }

  bool operator==(const GameStats& other) const                  { return rolls ==  other.rolls; }
  std::strong_ordering operator<=>(const GameStats& other) const { return rolls <=> other.rolls; }
};

struct ThreadResult {  

private:
  // trying an estimate for reserving ShortestGame vector
  static constexpr int _estimate_rolls = (settings::board::cols * settings::board::rows) / settings::dice::faces;

public: 
    
  ThreadResult();
  
  double avrg_rolls;
  std::unordered_map<cmn::board_int_t, unsigned> snakes_ladders_hits;
  GameStats shortest_game;

};


inline ThreadResult::ThreadResult()
: avrg_rolls{}, snakes_ladders_hits{}
{  
  using namespace settings::board;

  // get the keys ( the absolute origins ) and set their values to 0
  constexpr auto view = snakes_and_ladders::list::to_absolute_positions<cmn::board_int_t, cols, rows>(settings::board::snakes_and_ladders) 
    | std::ranges::views::transform([](const auto& val_pair) { return std::pair{val_pair.first, 0}; });

  // assign to unordered_map and reserve some space to vector
  snakes_ladders_hits.insert(view.begin(), view.end());
  shortest_game.roll_sequence.reserve(_estimate_rolls);
}

#endif
