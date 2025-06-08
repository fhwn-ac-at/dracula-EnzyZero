#ifndef settings_h 
#define settings_h 

#include "common.h"

namespace settings { 

/** 
 * @brief specify the dimensions of the board, snakes and ladders here
 * 
 *  The snakes_and_ladders list is a std::array with a pair of two vectors. 
 *  Each pair specifies the xy coords o the origin and the destination with the lower left corner of the board being
 *  the start of the kartesian coordinate sytem.
 *  
 *  @warning **coords start at 1!** for convenience
 *
 *  The goal of the board is at the opposite of the beginning, so in the upper right corner relative to the origin.
 */
namespace board 
{ 
  
  constexpr unsigned cols = 10;
  constexpr unsigned rows = 10; 
 
  constexpr cmn::snakes_and_ladders_list_t<unsigned, cols, rows>
    snakes_and_ladders = {{
        
    /* origin xy | dest xy  */
      { {1, 1},   { 10, 10} }, 

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
  constexpr cmn::dice_weights_list_t<unsigned, faces> weights = {};
}

} // settings namespace 

#endif
