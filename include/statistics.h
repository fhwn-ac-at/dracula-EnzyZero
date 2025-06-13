#ifndef statistics_collector_h
#define statistics_collector_h

#include <vector>
#include <unordered_map>
#include <numeric>
#include <compare>

struct Statistics {

  double avrg_rolls;
  std::vector<unsigned> shortest_game_rolls; 
  std::unordered_map<size_t, unsigned> snakes_ladders_hits;
 
  std::strong_ordering operator<=>(const Statistics& other) { return shortest_game_rolls.size() <=> other.shortest_game_rolls.size(); }
}; 

class StatisticsCollector {
public:

  void add_roll(const unsigned roll) { _current_game_roll_seq.push_back(roll); }

  void add_snake_ladder_hit(const size_t hit) { _snake_ladder_hit_map[hit]++; }

  void finalize() {

    // add current amount of rolls
    _all_game_roll_counts.push_back( _current_game_roll_seq.size() );

    // save whichever game was shortest
    if (_shortest_game_roll_seq.empty() ||
        _current_game_roll_seq.size() < _shortest_game_roll_seq.size())
      _shortest_game_roll_seq = std::move(_current_game_roll_seq); 

    _current_game_roll_seq.clear();
  }

  [[nodiscard]] Statistics get_results() {
    
    return {
      .avrg_rolls = std::accumulate(_all_game_roll_counts.begin(), _all_game_roll_counts.end(), 0) / static_cast<double>( _all_game_roll_counts.size() ),
      .shortest_game_rolls = std::move(_shortest_game_roll_seq),
      .snakes_ladders_hits = std::move(_snake_ladder_hit_map)
    };
  }
 
private:
  std::vector<unsigned> _current_game_roll_seq;
  std::vector<unsigned> _shortest_game_roll_seq;
  std::vector<unsigned> _all_game_roll_counts;

  std::unordered_map<size_t /* snake/ladder pos */, unsigned /* hit count */>
    _snake_ladder_hit_map;

  friend class StatisticsCollectorFactory;
}; 

template <size_t K>
class StatisticsCollectorFactory { 
public:
 
  constexpr StatisticsCollectorFactory(const std::span<unsigned> keys, const size_t reserve = 100)
  : _keys(keys.begin(), keys.end()),  _reserve(reserve)
  {} 

  StatisticsCollector create_collector() const {
    
    StatisticsCollector ret;
    ret._all_game_roll_counts.reserve(_reserve);
    ret._shortest_game_roll_seq.reserve(_reserve);
    ret._current_game_roll_seq.reserve(_reserve);
    ret._snake_ladder_hit_map.insert(_keys.begin(), _keys.end());
    return ret;
  }

  StatisticsCollector operator()() const { return create_collector(); }

private:
  const std::array<unsigned, K> _keys;
  const size_t _reserve;
};

#endif
