cmake_minimum_required(VERSION 4.0)

project(spatial-node-tree VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glm CONFIG REQUIRED)

include(erased.cmake)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${erased_SOURCE_DIR}/erased/include)
