cmake_minimum_required(VERSION 3.24)
project(
  exx_example
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(ext)
add_subdirectory(examples)
