#ifndef settings_h 
#define settings_h 

#include "dice.h"
#include "snakes_ladders_list.h"

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
 *  You may change the "goal_hit_exact" bool to set whether the a win is defined by hitting the goal exactly.
 *  If it is set to false, overshooting the goal will be a win as well.
 */
namespace board 
{  
  constexpr bool goal_hit_exact = true;
  
  constexpr unsigned cols = 10;
  constexpr unsigned rows = 10; 
 
  constexpr snakes_and_ladders::list::type<unsigned, cols, rows>
    snakes_and_ladders = {{
        
   /* origin xy |  dest xy     */
      { {1, 1},   { 10, 10} }, 

    }};
}  

/** 
 * @brief specify the faces and the weights (optional) of each of them 
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
  constexpr ::dice::weights_list_t<unsigned, faces> weights = {};
}

} // settings namespace 

#endif
