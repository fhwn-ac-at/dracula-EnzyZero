#ifndef board_init_h
#define board_init_h

#include "board_base.h"
#include "snakes_ladders_list.h"

namespace snakes_and_ladders {
  
template <std::integral T, size_t C = 10, size_t R = 10> 
class board : public board_base<T, C, R> {  
public:

  /** 
   * @brief custom constructor whcih accepts and initializer list holding multiple fields
   * @exception Constructor may throw a std::logic_error if snakes or ladders are misplaced
  */
  constexpr board(const snakes_and_ladders::list<T, C, R>& list);

private:
  using _base = board_base<T, C, R>; 
};   


template <std::integral T, size_t C, size_t R>
constexpr board<T, C, R>::board(const snakes_and_ladders::list<T, C, R>& list)
: _base{}
{ 
    assert(list && "List is invalid");

    // a second board which will be used to check for double destinations 
    // (big memory usage, but O(1) access, and I dont wanna use unordered_map)
    std::array<T, C * R> used_dest{}; 

    auto is_not_empty_pair = [](const auto& pair) { return pair.first != 0 || pair.second != 0; };
 
    // convert list to absolute positions and take until empty found
    for(const auto [ abs_origin, abs_dest ] : list.to_abs_positions() | std::ranges::views::take_while(is_not_empty_pair)) 
    { 
      // check for false snakes or ladder placement
      if (_base::_arr.at(abs_origin) != 0 || 
          _base::_arr.at(abs_dest)   != 0 ||
          used_dest.at(abs_dest)     != 0)
      {  
        _base::_init = false;
        return;
      } 

      // save the absolute index of the destination to an origin field 
      _base::_arr[abs_origin] = used_dest[abs_dest] = abs_dest;  
    } 

  _base::_init = true;
} 

} // snakes and ladders namespace

#endif
