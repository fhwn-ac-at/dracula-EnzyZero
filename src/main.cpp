#include <fmt/core.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h> 
#include <argparse/argparse.hpp>
#include <ctime>
#include <ranges>
#include <atomic>
#include <chrono>

#include "statistics.h"
#include "thread_cb.h"
#include "../settings.h"  
#include "snakes_ladders_board.h" 

int main(int argc, char* argv[]) {  

  using namespace settings;  

  // create board and init weights at compile-time
  snakes_and_ladders::board<unsigned, board::cols, board::rows> 
    board(board::snakes_and_ladders); 

  spdlog::set_pattern("[%^%l%$] %v");

  // check for success
  if (!board)
  {
    spdlog::error("BOARD::INIT::ERROR Board could not be created, check your settings.h");
    return 1;
  }
  else
    spdlog::info("BOARD::INIT::SUCCESSFUL Board was loaded successfully"); 

  size_t runs{};
  int time{};
  int threads{};
  int seed{ static_cast<int>(std::time(nullptr)) };
 
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
  
  // mark end time, init deadline checker
  const auto deadline = time > 0 
    ? std::chrono::steady_clock::now() + std::chrono::milliseconds(time)
    : std::chrono::steady_clock::time_point::max();

  /** 
   * @brief Setting up the threads
   *
   * First, the keys will be extracted from the snakes_and_ladders list and passed to the factory.
   * The factory is there to pre-insert keys into the map and reverve some stuff for the vectors to optimize a little
   * and avoid rehashing.
   *
   * Then the threads will be created. They take a lot of parameters. First the number of runs required is split equally
   * among the threads with a loop and they are called with their own statistics analyzer created from a factory.
   * The threads promise to return Statistics structs, unless they are stopped by the timer.
   */
 
  // vector for the returns of the threads
  std::vector<std::future<Statistics>> future_vec;
  future_vec.reserve(threads);

  // threads will be stopped as soon as the vector leaves this scope
  {
    // extract keys
    auto keys = std::views::keys(board::snakes_and_ladders.to_absolute());

    StatisticsCollectorFactory<board::snakes_and_ladders.size()> factory(keys, optional::reserve);
    std::atomic_size_t global_runs_left = runs;
    std::atomic_int threads_started = 0;

    std::vector<std::jthread> thread_vec;
    thread_vec.reserve(threads);

    // calculate the runs per thread. save the runs left to runs again 
    const unsigned per_thread_runs = runs / threads;
    runs -= per_thread_runs * (threads - 1);

    for (int i = 0; i < threads; i++)
    { 
      // make a promise
      std::promise<Statistics> promise;
      future_vec.push_back( promise.get_future() );

      thread_vec.emplace_back(
        [ &, i, promise = std::move(promise)] (std::stop_token st) mutable { 

          spdlog::info("Thread [{}]: running {} games with mixed_seed {}", gettid(), i ? per_thread_runs : runs, seed + i);   
          threads_started++;

          task<unsigned, board::cols, board::rows, dice::faces>(
            st,
            spdlog::default_logger(),
            global_runs_left,
            i ? per_thread_runs : runs, // the first thread gets the rest
            seed + i,
            dice::weights,
            board,
            factory.create_collector(),
            std::move( promise )
          );
        } // lambda
      ); // emplace back
    } // for

    // wait for all threads to have started 
    while (threads_started.load() < threads)
      std::this_thread::sleep_for( std::chrono::milliseconds(10) );


    fmt::print("\033[?25l\n"); // hide cursor
 
    // report runs left util either deadline reached or all runs finished
    while ( std::chrono::steady_clock::now() < deadline && global_runs_left.load() > 0)
      fmt::print("[{}RUNS::LEFT{}]: {}\r", "\033[34m", "\033[0m", global_runs_left.load());

    fmt::print("\033[?25h\n"); // show cursor

    if ( std::chrono::steady_clock::now() >= deadline )
      spdlog::warn("TIMER::EXPIRED");

  } // threads get stopped and deleted here - end of scope

  /** 
   * @brief collect the results
   *
   * A vector will hold all the Statistics objects.
   * A StatisticsCollector will be constructed with the vector and will sum all the results of each vector into
   * another Statistics obj whose members will be printed to stdout.
   */
  std::vector<Statistics> results;
  results.reserve(future_vec.size());
 
  for (auto& future : future_vec) 
  {  
    try {
       results.emplace_back( future.get() );

    } catch (std::exception& err) {
      spdlog::error("BROKEN::PROMISE::ERROR: {}", err.what());
      return 1;
    }
  }
 
  StatisticsCollector final_collect(results);
  Statistics result = final_collect.get_results(); 

  fmt::println("      AVERAGE_ROLLS: {} rolls to win a game on average", result.avrg_rolls);
  fmt::println("  SHORTEST_ROLL_SEQ: {}", result.shortest_game_rolls);
  fmt::println("SNAKES_LADDERS_HITS: dest  |  hits ", result.snakes_ladders_hits.size());

  // print all the pairs
  for (const auto& pair : result.snakes_ladders_hits)
    fmt::println("                    {:^7}|{:^7}", pair.first, pair.second);
}
