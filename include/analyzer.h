#ifndef analyzer_h
#define analyzer_h

#include <vector>
#include <unordered_map> 

#include "game.h"

class Analyzer {
public: 

  struct Statistics {

    double avrg_rolls;
    std::vector<unsigned> shortest_game_rolls; 
    std::unordered_map<size_t, unsigned> snakes_ladders_hits;
  };  

  Analyzer() = default;

  void finalize() {

    if (_current_game_roll_seq.size() < _shortest_game_roll_seq.size())
      _shortest_game_roll_seq = std::move(_current_game_roll_seq); 

    _current_game_roll_seq.clear();
  }

private:
  std::vector<unsigned> _current_game_roll_seq;
  std::vector<unsigned> _shortest_game_roll_seq;

  std::unordered_map<size_t /* snake/ladder pos */, unsigned /* hit count */>
    _snake_ladder_hit_map;
};

#endif
