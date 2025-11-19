
add_executable(spacegraph_tests
    test_constructor_node.cpp
    test_matrix_trait.cpp
    test_transform_node.cpp
)

target_include_directories(spacegraph_tests PRIVATE ../include)

if(MSVC)
    target_compile_options(spacegraph_tests PRIVATE /W4 /WX)
else()
    target_compile_options(spacegraph_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(spacegraph_tests PRIVATE
    Catch2::Catch2 Catch2::Catch2WithMain
    glm::glm-header-only
    Qt6::Core Qt6::Gui
)

if(NOT HAVE_MDSPAN)
    target_link_libraries(spacegraph_tests PRIVATE std::mdspan)
endif()

include(Catch)
catch_discover_tests(spacegraph_tests)
