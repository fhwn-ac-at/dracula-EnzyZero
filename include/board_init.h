#ifndef board_init_h
#define board_init_h

#include "common.h"

// initialise a board with snakes and ladders at compile-time
template <std::size_t C, std::size_t R>
consteval auto board_init(const common::snakes_and_ladders_list_t<C, R>& list) -> common::board_t<C, R> { 
 
  common::board_t<C, R> ret_board{};  

  for(const auto [origin, dest] : list) 
  {  
    if (ret_board.at(origin) != 0) throw "Cannot declare two snakes or ladders to begin at the same origin";
    if (ret_board.at(dest)   != 0) throw "Cannot declare the destination of a snake or ladder at a onother origin";
    ///@warning duplicate destinations not checked

    // save the index of the destination to this field
    ret_board.at(origin) = dest; 
  } 

  return ret_board;
}

#endif
