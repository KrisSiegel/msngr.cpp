# msngr.cpp
This version of msngr is written in C++ and designed to handle messaging interal to your application.

## Getting started
You'll need a C++ compiler capable of at least C++ 14 with STL experiments (needed for `std::optional`). Beyond that, msngr.cpp is a header only library so you shouldn't need much else.

1. Copy `msngr.hpp` to your include directory
2. Reference `msngr.hpp`
3. Compile with a C++17 capable compiler. Some compilers, like `g++`, may require passing the flag `-std=gnu++1y` to compile correctly.

## Usage
This current version is a very early, prerelease version of msngr. This means its capabilities are extremely limited and likely prone to bugs. Your milage may very.

See the `main.cpp` file for usage examples.

## Compile and run
If you have gcc installed then `g++ src/main.cpp -std=gnu++1y -o msngr && ./msngr` should do the trick.