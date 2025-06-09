#ifndef statistic_containers_h
#define statistic_containers_h

#include <vector>
#include <unordered_map>
#include <compare> 

#include "common.h"
#include "../settings.h" 

struct GameStats {

  unsigned rolls{};
  std::vector<int> roll_sequence; 

  void reset() { rolls = 0; roll_sequence.clear(); }

  bool operator==(const GameStats& other) const                  { return rolls ==  other.rolls; }
  std::strong_ordering operator<=>(const GameStats& other) const { return rolls <=> other.rolls; }
};

struct ThreadResult {  

private:
  // trying an estimate for reserving ShortestGame vector
  static constexpr int estimate_rolls = (settings::board::cols * settings::board::rows) / settings::dice::faces; 

public: 
    

  ThreadResult()
  : avrg_rolls{}, snakes_ladders_hits{}
  {
    // map will use as many keys as there are snakes and ladders
    snakes_ladders_hits.reserve(settings::board::snakes_and_ladders.size());
    shortest_game.roll_sequence.reserve(estimate_rolls);
  }
  
  double avrg_rolls;
  std::unordered_map<cmn::board_int_t, unsigned> snakes_ladders_hits;
  GameStats shortest_game;

};

#endif
