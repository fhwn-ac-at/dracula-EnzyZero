#ifndef settings_h 
#define settings_h 

#include "common.h"

namespace settings { 

/** 
 * @brief specify the dimensions of the board, snakes and ladders here
 * 
 *  The snakes_and_ladders list is a std::array with std::pairs. 
 *  Each pair specifies the absolute distance from the first field of the board to the origin
 *  and the destination.
 *
 *  @warning This means that THESE ARE NO X/Y Coordinates
 *  
 *  E.g. {10, 20} means that this ladder begins at field 10 and ends at field 20, with 
 *  **1 being the first field** 
 */
namespace board 
{ 
  
  constexpr unsigned cols = 10;
  constexpr unsigned rows = 10; 
 
  constexpr common::snakes_and_ladders_list_t<cols, rows>
    snakes_and_ladders = {{

      {10, 20},
      {30, 80},
      {99, 5} 

    }};
}  

/** 
 * @brief speficy the faces and the weights (optional) of each of them 
 *
 * The faces are self-explanatory.
 * 
 * The weights array makes it possible to specify a non-uniform distribution.
 * Note that if a uniform distribution is required, the list should either be set to empty
 * or contain n numbers (n = faces) with the same value.
 * 
 * @warning If a non-uniform dist. is wanted, you MUST specify as many weights as there are faces 
 * In the background, std::discrete_distribution is used.
 */
namespace dice 
{
  constexpr unsigned faces = 6; 
  constexpr common::dice_weights_list_t<faces> weights = {};
}

} // settings namespace 

#endif
