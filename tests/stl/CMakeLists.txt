add_executable(tests_stl
    test_constructor_node.cpp
    test_matrix_trait.cpp
    test_transformation_node.cpp
)

target_compile_definitions(tests_stl PRIVATE TYPE=StlMatrix4)

catch_discover_tests(tests_stl)
