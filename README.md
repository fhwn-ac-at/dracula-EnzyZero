# Building

This project uses conan to install some libraries. For some reason, the profile __needs to declare the gcc compiler__ as compiling ncurses with clang did not work. You may later tell cmake to build the project with clang etc., this is just necessary for installing ncurses. Please also make sure you have make, cmake and conan installed before attempting to install. 
For example, these were my settings for the conan profile:

```sh
[settings]
arch=x86_64
build_type=Release
compiler=gcc # gcc necessary for ncurses
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux

```

Then install the libraries with conan and compile using cmake.
The binary will be located in either `build/Release/` or `build/Debug/` depending on the `build_type` setting chosen in the conan profile.

```sh
# autodetect conan profile
conan profile detect # --name=<profile_name> optional

# in project root directory
conan install . --build=missing # --profile=<profile_name> optional

# build project
cmake --preset conan-release
cmake --build --preset conan-release
```

# Model

The picture below shows the rough model of how the classes are implemented to work with each other.

![dracula interpreter model](dracula_interpreter_model.png)

## Commands, grid and hashtable

Each command-char is implemented in its own callable derived from a command_base class interface. The callables for the commands are registered to a hashtable, which itself is plugged into the interpreter coroutine.
Furthermore, a grid-class is defined, which takes the data in a file as input and provides a cursor to move around the stack-allocated grid in the object.

## Interpreter coroutine

The interpreter class takes a hashtable with the commands and the grid. Additionally, it takes a specific buffer/stream for input and output (as some commands work with those), a stack and a spdlog::logger for logging stuff. The design aims to maximise testablity. Later, the streams will be set to stdout and stdin as in the assignment.
I chose to use a coroutine as the UI depends on small stops in the execution to show the intermediate steps to the user. Also, I wanted to use them (lol). The coroutine keeps the logic contained and there is no need to add a `this_thread::sleep_for` anywhere in the interpreter logic. This will be done in a loop in the main function. 

## UI

I tried to keep the interface between the logic-handling stuff and the frontend as minimal as possible (like with the coro). Therefore, the Ncurses class is a friend of most of the backend-classes and gets access to the internals. An update function then prints all the current states to the screen.
