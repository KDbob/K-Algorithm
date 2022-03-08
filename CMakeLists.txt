cmake_minimum_required(VERSION 3.17)
project(K_Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(LCS LCS/main.cpp)
add_executable(MatrixChain MatrixChain/main.cpp)
add_executable(Backtrack Backtrack/main.cpp)
add_executable(Selector Selector/main.cpp)

add_executable(Climbing Climbing/main.cpp)
add_executable(LocalSearch LocalSearch/main.cpp)
add_executable(LocalSearch-Op LocalSearch-Op/main.cpp)

add_executable(N-Queens-SA N-Queens-SA/main.cpp)
add_executable(N-Queens-SA-Test N-Queens-SA-Test/main.cpp)

add_executable(Searching Searching/main.cpp)
add_executable(RouletteChoice RouletteChoice/main.cpp)