cmake_minimum_required(VERSION 3.25.3)
project(dracula-EnzyZero)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set flags for each build type
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG_MODE")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

# Find libraries
find_package(Curses REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Dirs to resources
set(INCLUDEDIR ${CMAKE_SOURCE_DIR}/include)
set(SRCDIR ${CMAKE_SOURCE_DIR}/src)
set(TESTDIR ${CMAKE_SOURCE_DIR}/test)

# collect all cpp files in src
file(GLOB SOURCES ${SRCDIR}/*.cpp)

# Tests are built in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    include(CTest)

    message(STATUS "enable_testing(): Building Tests... run ctest to execute them once built")
    enable_testing()

    # Remove main.cpp and append all cpp files in test folder to sources
    list(REMOVE_ITEM SOURCES "${SRCDIR}/main.cpp")
    file(GLOB TEST_SOURCES ${TESTDIR}/*.cpp)
    list(APPEND SOURCES ${TEST_SOURCES})

    add_executable(test_dracula ${SOURCES})
    target_link_libraries(test_dracula PRIVATE
        Curses::Curses
        GTest::gtest
        GTest::gtest_main
        spdlog::spdlog
        fmt::fmt
    )

    # automate registering tests to ctest
    include(GoogleTest)
    gtest_discover_tests(test_dracula)

else() # Release

    add_executable(dracula main.cpp) 
    message(STATUS "Tests disabled")

    target_link_libraries(dracula PRIVATE
        Curses::Curses
        spdlog::spdlog
        fmt::fmt
    )

endif()



