#ifndef board_init_h
#define board_init_h

#include "board.h"
#include "common.h"
#include <initializer_list> 
#include <format>
#include <stdexcept>

template <std::integral T, size_t C = 10, size_t R = 10> 
class SnakesLaddersBoard : public Board<T, C, R> {  
public:

  // using cstr's of Board
  using Board<T, C, R>::Board; 

  /** 
   * @brief custom constructor whcih accepts and initializer list holding multiple fields
   * @exception Constructor may throw a std::logic_error if snakes or ladders are misplaced
  */
  constexpr SnakesLaddersBoard(const std::initializer_list<T>& list);

  /**
   * @brief Use this consteval func to convert a snakes_and_ladders list into a board
  */
  static consteval auto init_board(const cmn::snakes_and_ladders_list_t<T, C, R>& list) -> SnakesLaddersBoard<T, C, R>;  

private:
  using Board_t = Board<T, C, R>; 
};   


template <std::integral T, size_t C, size_t R>
constexpr SnakesLaddersBoard<T, C, R>::SnakesLaddersBoard(const std::initializer_list<T>& list) 
: Board_t::_arr{}, Board_t::_init( false )
{ 
  // a second board which will be used to check for double destinations 
  // (big memory usage, but O(1) access, and I dont wanna use unordered_map)
  std::array<T, C * R> used_dest{};

  for(int i = 0; i < list.length(); i++) 
  {      
    const T dest = list.at(i); 

    // check for false snakes or ladder placement
    if (Board_t::_arr.at(i)    != 0 || 
        Board_t::_arr.at(dest) != 0 ||
        used_dest.at(dest)     != 0)
    { 
      throw std::logic_error(std::format(
        "STUPID::SNAKES::LADDER::PLACEMENT duplicate origin: {0} destination is an origin: {1} duplicate destination: {2}", 
        Board_t::_arr.at(i)    == 0,
        Board_t::_arr.at(dest) == 0,
        used_dest.at(dest)     == 0)
      );
    }

    // save the index of the destination to this field
    Board_t::_arr.at(i) = used_dest.at(dest) = dest;  
  } 

  Board_t::_init = true;
}

template <std::integral T, size_t C, size_t R>
consteval auto SnakesLaddersBoard<T, C, R>::init_board(const cmn::snakes_and_ladders_list_t<T, C, R>& list) -> SnakesLaddersBoard<T, C, R> {
 
  SnakesLaddersBoard<T, C, R> ret_board{};  
  ret_board.valid(false);
 
  auto null_vec  = [](cmn::vector<T> vec) -> bool { return !vec.x && !vec.y; };
  auto check_vec = [](cmn::vector<T> vec) -> bool { return vec.x <= 0 || vec.x > C || vec.y <= 0 || vec.y > R; };

  for(auto [ origin_vec, dest_vec ] : list) 
  {   
    if ( null_vec(origin_vec) || null_vec(dest_vec) ) 
        break; 

    else if ( check_vec(origin_vec) || check_vec(dest_vec) )
      return ret_board; 
  
    origin_vec.y--;
    origin_vec.x--;
    dest_vec.y--;
    dest_vec.x--;

    // save the absolute index of the destination to this field
    ret_board[origin_vec.y * R + origin_vec.x] = dest_vec.y * R + dest_vec.x;  
  } 
  
  ret_board.valid(true);
  return ret_board;
}

#endif
