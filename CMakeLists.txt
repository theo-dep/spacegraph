cmake_minimum_required(VERSION 4.0)

project(spacetree VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glm CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(Catch2 CONFIG REQUIRED)

include(cmake/erased.cmake)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ctest --test-dir=tests)
add_subdirectory(tests)
