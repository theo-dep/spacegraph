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
        using Transformable = erased::erased<Multiply, erased::Copy, erased::Move>;

        struct Multiply
        {
            constexpr static std::optional<Transformable> invoker(const auto& self, const Transformable& other)
            {
                using SelfType = std::remove_cvref_t<decltype(self)>;
                if (erased::is<SelfType>(other))
                    return matrix_trait<SelfType>::multiply(self, erased::any_cast<SelfType>(other));
                return std::nullopt;
            }

            constexpr std::optional<Transformable> multiply(this const auto& erased, const Transformable& other)
            {
                return erased.invoke(Multiply{}, other);
            }
        };

    }

    struct Node
    {
        std::optional<details::Transformable> transform_to(const Node& /*other*/) { return std::nullopt; }
    };

}
