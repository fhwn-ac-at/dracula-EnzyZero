#include <fmt/core.h>
#include <spdlog/spdlog.h> 

#include "../settings.h"  
#include "snakes_ladders_board.h"

using namespace settings::board;
using SLBoard = SnakesLaddersBoard<unsigned, cols, rows>;

constexpr SLBoard board = SLBoard::init_board(snakes_and_ladders);    

int main() {    

  spdlog::set_pattern("[%^%l%$] %v");

  if constexpr (!board)
    spdlog::error("BOARD::INIT::ERROR Board could not be created at compile-time, check your coordinates");
  else
    spdlog::info("BOARD::INIT::SUCCESSFUL Board was loaded at compile-time");

}
