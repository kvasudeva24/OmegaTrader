#set the min required version
cmake_minimum_required(VERSION 3.15)

#set the project name internally
project(OmegaTrader)

#using c++20 and make sure
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#to add Catch2 test suite
include(FetchContent)

#add catch2
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
)

#download build and make catch2 usuable
FetchContent_MakeAvailable(Catch2)

#add test executable
add_executable(tests
    tests/test_order.cpp
    src/Order.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)