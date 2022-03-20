cmake_minimum_required(VERSION 3.17)
project(K_Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(N-Queens Searching/Backtrack/N-Queens/main.cpp)
add_executable(LCS "Dynamic/LCS/main.cpp")
add_executable(MatrixChain "Dynamic/MatrixChain/main.cpp")
add_executable(Backtrack "Searching/Backtrack/N-Queens/main.cpp")
add_executable(Selector "Divide/Selector/main.cpp")

add_executable(Climbing "Searching/Local Search/Climbing/main.cpp")
add_executable(LocalSearch "Searching/Local Search/LocalSearch/main.cpp")
add_executable(LocalSearch-Op "Searching/Local Search/LocalSearch-Op/main.cpp")

add_executable(N-Queens-SA "Searching/Local Search/N-Queens-SA/main.cpp")
add_executable(N-Queens-SA-Test "Searching/Local Search/N-Queens-SA-Test/main.cpp")

add_executable(local_search "Searching/Local Search/Searching/main.cpp")
add_executable(RouletteChoice "Searching/Local Search/RouletteChoice/main.cpp")