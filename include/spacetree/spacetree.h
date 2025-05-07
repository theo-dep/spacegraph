#pragma once

#include <erased/erased.h>

#include <optional>

template <typename T>
struct matrix_trait
{
    static_assert(false, "Must be implemented for your own matrix type");
    static void set_identity(T& self);
    static T multiply(const T& self, const T& other);
};

namespace spacetree
{

    namespace details
    {

        struct Identity;
        struct Multiply;
        using Transformable = erased::erased<Identity, Multiply, erased::Copy, erased::Move>;

        struct Identity
        {
            constexpr static void invoker(auto& self)
            {
                using SelfType = std::remove_cvref_t<decltype(self)>;
                matrix_trait<SelfType>::set_identity(self);
            }

            constexpr void set_identity(this auto& erased)
            {
                return erased.invoke(Identity{});
            }
        };

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

    struct Node final
    {
        template <typename T>
        constexpr Node(std::in_place_type_t<T> t, auto&&... args)
            : _transform(t, std::forward<decltype(args)>(args)...)
        {
            _transform.set_identity();
        }

        template <typename T>
        constexpr Node(T x)
            : Node{ std::in_place_type<T>, std::forward<T>(x) }
        {
        }

        constexpr ~Node() = default;
        constexpr Node(const Node&) = default;
        constexpr Node(Node&&) = default;
        constexpr Node& operator=(const Node&) = default;
        constexpr Node& operator=(Node&&) = default;

        constexpr std::optional<details::Transformable> transform_to(const Node& other)
        {
            if (std::addressof(other) == this)
                return _transform;
            return std::nullopt;
        }

    private:
        details::Transformable _transform;
    };

}
