cmake_minimum_required(VERSION 3.20)
project(SpaceGraph VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CheckCXXSymbolExists)
check_cxx_symbol_exists(std::mdspan "mdspan" HAVE_MDSPAN)

find_package(glm CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(Catch2 CONFIG REQUIRED)

if(NOT HAVE_MDSPAN)
    find_package(mdspan CONFIG REQUIRED)
endif()

enable_testing()
add_subdirectory(tests)
