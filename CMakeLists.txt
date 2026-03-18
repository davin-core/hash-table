cmake_minimum_required(VERSION 3.10)
# set the project name
project(hash_table LANGUAGES CXX VERSION 1.0)


# required C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add the executable
add_executable(main
    src/main.cpp
    src/hash_table.cpp
    src/prime.cpp
)
