#include <fmt/core.h> 
#include <spdlog/spdlog.h> 
#include <argparse/argparse.hpp>
#include <ctime>

#include "../settings.h"  
#include "snakes_ladders_board.h" 

int main(int argc, char* argv[]) {  

  using namespace settings;

  // crate board and init weights at compile-18:27
  constexpr snakes_and_ladders::board<unsigned, board::cols, board::rows> 
    board(board::snakes_and_ladders);

  spdlog::set_pattern("[%^%l%$] %v");

  // check for success
  if constexpr (!board)
  {
    spdlog::error("BOARD::INIT::ERROR Board could not be created at compile-time, check your settings.h");
    return 1;
  }
  else
    spdlog::info("BOARD::INIT::SUCCESSFUL Board was loaded successfully at compile-time\n"); 

  int runs{};
  int time{};
  int threads{};
  int seed{ static_cast<int>(std::time(NULL)) };
 
  // handle cli arguments using argsparser library
  { 
    argparse::ArgumentParser program("SnakesAndLadders Monte-Carlo Simulator");

    program.add_argument("-r", "--runs")
      .help("Specify how many runs should be simulated")
      .required()
      .store_into(runs);

    program.add_argument("-t", "--time")
      .help("Set a time limit (in milliseconds), 0 meaning no limit.")
      .default_value(0)
      .store_into(time);

    program.add_argument("-j", "--threads")
      .help("Set how many threads should be used.")
      .default_value(1)
      .store_into(threads);

    program.add_argument("-s", "--seed")
      .help("Set a seed to be used for the RNGs")
      .store_into(seed);

    // print help for no-args
    if (argc == 1)
    {
      std::cout << program << '\n';  
      spdlog::warn("NO::ARGS::GIVEN no arguments passed, exiting");
      return 0;
    }
  
    // parsing happens here
    try 
    { 
      program.parse_args(argc, argv);
    } 
    catch (const std::exception& err) 
    {
      spdlog::error("ARGS::PARSING::ERROR {}", err.what());
      std::cerr << program;
      return 1;
    } 

    // some boilerplate checks
    if (threads < 1)
    {
      spdlog::error("INVALID::ARG::ERROR threads arg must be > 0. Got: {}", threads);
      return 1;
    }
    else if (time < 0)
    {
      spdlog::error("INVALID::ARG::ERROR time arg must be >= 0. Got {}", time);
      return 1;
    }
    else if (runs < 1)
    {
      spdlog::error("INVALID::ARG::ERROR runs must be >= 1. Got {}", runs);
      return 1;
    }
  } 

  spdlog::info("Seed used: {}", seed);
  spdlog::info("Starting the simulator. Running {} times on {} threads for {} milliseconds", runs, threads, time ? std::to_string(time) : "infinite"); 

  //std::atomic_int at_runs = runs;

  // TODO signal handler?
}
