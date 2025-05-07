add_executable(tests_qt
    test_matrix_trait.cpp
    test_transformation_node.cpp
)

target_compile_definitions(tests_qt PRIVATE TYPE=QMatrix4x4)

add_dependencies(tests_qt generate_amalgamated)

catch_discover_tests(tests_qt)
