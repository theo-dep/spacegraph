add_executable(tests_glm
    test_constructor_node.cpp
    test_matrix_trait.cpp
    test_transformation_node.cpp
)

target_compile_definitions(tests_glm PRIVATE TYPE=glm::mat4)

target_link_libraries(tests_glm PRIVATE glm::glm-header-only)

add_dependencies(tests_glm generate_amalgamated)

catch_discover_tests(tests_glm)
