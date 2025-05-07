add_executable(tests_glm
    test_matrix_trait.cpp
    test_transformation_node.cpp
)

target_compile_definitions(tests_glm PRIVATE TYPE=glm::mat4)

catch_discover_tests(tests_glm)
