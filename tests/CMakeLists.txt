get_filename_component(TESTS_TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${TESTS_TARGET_NAME})

add_subdirectory(glm)
add_subdirectory(qt)

target_include_directories(${TESTS_TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${erased_SOURCE_DIR}/erased/include
    ${CMAKE_SOURCE_DIR}/tests
)

target_compile_definitions(${TESTS_TARGET_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_compile_options(${TESTS_TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(${TESTS_TARGET_NAME} PRIVATE
    glm::glm-header-only
    Qt6::Core Qt6::Gui
    Catch2::Catch2 Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(${TESTS_TARGET_NAME})
