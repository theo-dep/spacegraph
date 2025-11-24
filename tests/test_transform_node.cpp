#include "test.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("Transformation to another node failure", "[transform_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    const auto bool_transform_to = GENERATE(
        Catch::Generators::as<std::function<bool(const spacegraph::Node&, const spacegraph::Node&)>>{},

        [](const spacegraph::Node& node, const spacegraph::Node& other_node) {
            return node.transform_to<TestType>(other_node);
        },
        [](const spacegraph::Node& node, const spacegraph::Node& other_node) {
            bool actual{ false };
            node.transform_to(other_node)
                .and_then([&](const TestType&) { actual = true; })
                .or_else([&] { actual = false; });
            return actual;
        });

    SECTION("")
    {
        spacegraph::Node node;
        REQUIRE_FALSE(bool_transform_to(node, node));
    }
}

TEMPLATE_TEST_CASE("Transformation to another node successful", "[transform_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    const auto transform_to = GENERATE(
        Catch::Generators::as<std::function<TestType(const spacegraph::Node&, const spacegraph::Node&)>>{},

        [](const spacegraph::Node& node, const spacegraph::Node& other_node) {
            const auto res{ node.transform_to<TestType>(other_node) };
            CHECK(res);
            return *res;
        },
        [](const spacegraph::Node& node, const spacegraph::Node& other_node) {
            TestType actual;
            node.transform_to(other_node)
                .and_then([&](const TestType& res) { actual = res; })
                .or_else([] { FAIL(); });
            return actual;
        });

    SECTION("")
    {
        spacegraph::Node node(std::in_place_type<TestType>);
        REQUIRE(transform_to(node, node) == identity<TestType>());
    }

    SECTION("")
    {
        spacegraph::Node node(default_value<TestType>());
        REQUIRE(transform_to(node, node) == default_value<TestType>());
    }
}
