# Installation

This project uses conan to install some libraries. For some reason, the profile needs to declare the gcc compiler as compiling ncurses with clang did not work. Please also make sure to have make, cmake and conan installed before attempting to install. 
These were my settings for the conan profile.

```sh
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux

```

Then install the libraries with conan and compile using cmake:

```sh
# autodetect conan profile
conan profile detect # --name=<profile_name> optional

# in project root directory
conan install . --build=missing # --profile=<profile_name> optional

# build project
cmake --preset conan-release
cmake --build --preset conan-release
```





