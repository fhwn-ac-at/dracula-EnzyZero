#ifndef statistics_collector_h
#define statistics_collector_h

#include <cwchar>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <compare>
#include <algorithm>
#include <ranges>
#include <concepts>

template <std::integral T>
struct Statistics {

  double avrg_rolls;
  std::vector<T> shortest_game_rolls; 
  std::unordered_map<size_t, unsigned> snakes_ladders_hits;
 
  std::strong_ordering operator<=>(const Statistics<T>& other) { return shortest_game_rolls.size() <=> other.shortest_game_rolls.size(); }
}; 

template <std::integral T>
class StatisticsCollector {
public:

  void add_roll(const T roll) { _current_game_roll_seq.push_back(roll); }

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

  [[nodiscard]] Statistics<T> get_results() {
    
    return {
      .avrg_rolls = std::accumulate(_all_game_roll_counts.begin(), _all_game_roll_counts.end(), 0) / static_cast<double>( _all_game_roll_counts.size() ),
      .shortest_game_rolls = std::move(_shortest_game_roll_seq),
      .snakes_ladders_hits = std::move(_snake_ladder_hit_map)
    };
  }
 
private:
  std::vector<T> _current_game_roll_seq;
  std::vector<T> _shortest_game_roll_seq;
  std::vector<T> _all_game_roll_counts;

  std::unordered_map<size_t /* snake/ladder pos */, unsigned /* hit count */>
    _snake_ladder_hit_map;
 
  template <std::integral _T, size_t K>
  friend class StatisticsCollectorFactory;
}; 

template <std::integral T, size_t K>
class StatisticsCollectorFactory { 
public:
  
  template <std::ranges::input_range R>
  requires std::integral<std::ranges::range_value_t<R>>
  constexpr StatisticsCollectorFactory(R&& keys, const size_t reserve = 100)
  : _reserve(reserve)
  { 
    // copy the keys into the private array
    auto in_it = keys.begin();
    auto out_it = _keys_zerovalues.begin(); 

    for (; in_it != keys.end() && out_it != _keys_zerovalues.end(); in_it++, out_it++)
    { 
      out_it->first = *in_it;
      out_it->second = 0;
    }
  }

  StatisticsCollector<T> create_collector() const {
    
    StatisticsCollector<T> ret;
    ret._all_game_roll_counts.reserve(_reserve);
    ret._shortest_game_roll_seq.reserve(_reserve);
    ret._current_game_roll_seq.reserve(_reserve);
    ret._snake_ladder_hit_map.insert(_keys_zerovalues.begin(), _keys_zerovalues.end());
    return ret;
  }

  StatisticsCollector<T> operator()() const { return create_collector(); }

private:
  std::array<std::pair<T, T>, K> _keys_zerovalues; // map expects pairs to be inserted
  const size_t _reserve;
};

#endif
