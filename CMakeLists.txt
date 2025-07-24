# Set the minimum required version
cmake_minimum_required(VERSION 3.15)

# Set the project name internally
project(OmegaTrader)

# Use C++20 and enforce standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent to pull in external dependencies
include(FetchContent)

# Add Catch2 using FetchContent
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
)

# Download, build, and make Catch2 usable
FetchContent_MakeAvailable(Catch2)


# Add test executable
add_executable(tests
tests/test_EMA.cpp
src/EMA.cpp
src/OrderBook.cpp
src/Order.cpp
)

# Add include directories
target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${catch2_SOURCE_DIR}/include
)

# Link Catch2 to the test executable
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
