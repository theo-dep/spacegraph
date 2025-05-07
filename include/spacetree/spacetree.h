#pragma once

#include <erased/erased.h>

#include <optional>

template <typename T>
struct matrix_trait
{
    static_assert(false, "Must be implemented for your own matrix type");
    static T multiply(const T& self, const T& other);
};

namespace spacetree
{

    namespace details
    {

        struct Multiply;
        using Multipliable = erased::erased<Multiply, erased::Copy, erased::Move>;

        struct Multiply
        {
            constexpr static Multipliable invoker(const auto& self, const Multipliable& other)
            {
                using SelfType = std::remove_cvref_t<decltype(self)>;
                return matrix_trait<SelfType>::multiply(self, erased::any_cast<SelfType>(other));
            }

            constexpr Multipliable multiply(this const auto& erased, const Multipliable& other)
            {
                return erased.invoke(Multiply{}, other);
            }
        };

    }

    struct Node
    {
        std::optional<details::Multipliable> transform_to(const Node& /*other*/) { return std::nullopt; }
    };

}
