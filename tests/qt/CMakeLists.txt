add_executable(tests_qt
    test_constructor_node.cpp
    test_matrix_trait.cpp
    test_transformation_node.cpp
)

target_compile_definitions(tests_qt PRIVATE TYPE=QMatrix4x4)

target_link_libraries(tests_qt PRIVATE Qt6::Core Qt6::Gui)

add_dependencies(tests_qt generate_amalgamated)

catch_discover_tests(tests_qt)
