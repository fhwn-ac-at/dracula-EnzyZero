cmake_minimum_required(VERSION 3.25.3)
project(dracula-EnzyZero)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set flags for each build type
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG_MODE")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")  
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TESTING "Option for building tests" OFF)

# hack from https://www.reddit.com/r/cpp/comments/1b6f3s4/any_news_on_when_libc_is_going_to_support/
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Workaround for std::expected not available in clang
  add_compile_options(
    -stdlib=libstdc++ -D__cpp_concepts=202002 -Wno-builtin-macro-redefined -Werror -Wextra -Wall
  )
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

# Find libraries
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(argparse REQUIRED)
#find_package(Curses REQUIRED)

# Dirs to resources
set(INCLUDEDIR ${CMAKE_SOURCE_DIR}/include)
set(SRCDIR ${CMAKE_SOURCE_DIR}/src)
set(TESTDIR ${CMAKE_SOURCE_DIR}/tests)

# collect all cpp files in src 
file(GLOB SOURCES ${SRCDIR}/*.cpp)

# Tests are build if TESTING is on
if(TESTING)

    include(CTest)

    message(STATUS "enable_testing(): Building Tests... run ctest to execute them once built")
    enable_testing() 

    # Remove main.cpp and append all cpp files in test folder to sources
    list(REMOVE_ITEM SOURCES "${SRCDIR}/main.cpp")
    file(GLOB TEST_SOURCES ${TESTDIR}/*.cpp)
    list(APPEND SOURCES ${TEST_SOURCES}) 

    add_executable(test_dracula ${TEST_SOURCES})
    target_include_directories(test_dracula PRIVATE ${INCLUDEDIR})

    target_link_libraries(test_dracula PRIVATE
        GTest::GTest
        GTest::gtest_main 
        spdlog::spdlog
        fmt::fmt 
        argparse::argparse
    )

    # automate registering tests to ctest
    include(GoogleTest)
    gtest_discover_tests(test_dracula)

else() # not testing

    message(STATUS "Tests disabled") 

    add_executable(dracula ${SOURCES}) 
    target_include_directories(dracula PRIVATE ${INCLUDEDIR})  

    target_link_libraries(dracula PRIVATE
        spdlog::spdlog
        fmt::fmt
        argparse::argparse
        #Curses::Curses
    )

endif()
