#include <fmt/core.h>
#include "../settings.h"  
#include "board_init.h"

// well thats one horrible line of code
constexpr common::board_t<settings::board::cols, settings::board::rows>
  board = board_init<settings::board::cols, settings::board::rows>(settings::board::snakes_and_ladders);   

int main() {

  fmt::print("Board at 10 = {}", board[10]); 


}
