
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/tests
)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

link_libraries(
    glm::glm-header-only
    Qt6::Core Qt6::Gui
    Catch2::Catch2 Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

add_subdirectory(glm)
add_subdirectory(qt)
