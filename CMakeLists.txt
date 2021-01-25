cmake_minimum_required(VERSION 3.17)
project(Ex5)

set(CMAKE_CXX_STANDARD 98)

set(GCC_COVERAGE_COMPILE_FLAGS "−Wall −ansi −Wpedantic −Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Ex5 main.cpp Store.h StoreBase.h DataStore.h DataStoreImp.h)