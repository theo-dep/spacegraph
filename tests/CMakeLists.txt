
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/tests
)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

link_libraries(Catch2::Catch2 Catch2::Catch2WithMain)

include(CTest)
include(Catch)

add_subdirectory(glm)
add_subdirectory(qt)
add_subdirectory(stl)
