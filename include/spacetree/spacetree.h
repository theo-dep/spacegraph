#pragma once

#include <concepts>
#include <optional>

template <typename T>
struct matrix_trait
{
    // Must be implemented for your own matrix type
    // static void set_identity(T& self);
    // static T multiply(const T& self, const T& other);
};

namespace spacetree
{

    namespace details
    {

        template <typename T>
        concept IdentityInitializable = requires(T m) {
            { matrix_trait<T>::set_identity(m) } -> std::same_as<void>;
        };

        template <typename T>
        concept Multipliable = requires(T m) {
            { matrix_trait<T>::multiply(m, std::declval<T>()) } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Transformable = IdentityInitializable<T> && Multipliable<T>;

    }

    template <details::Transformable T>
    struct Node
    {
        constexpr Node() = default;

        constexpr Node(std::in_place_t)
            : _transform(T{})
        {
            matrix_trait<T>::set_identity(*_transform);
        }

        template <typename... Args>
        constexpr Node(std::in_place_t, Args&&... args)
            : _transform(std::in_place, std::forward<Args>(args)...)
        {
        }

        constexpr Node(T x)
            : Node{ std::in_place, std::forward<T>(x) }
        {
        }

        constexpr ~Node() = default;
        constexpr Node(const Node&) = default;
        constexpr Node(Node&&) = default;
        constexpr Node& operator=(const Node&) = default;
        constexpr Node& operator=(Node&&) = default;

        constexpr std::optional<T> transform_to(const Node& other) const
        {
            if (std::addressof(other) == this)
                return _transform;
            return std::nullopt;
        }

    private:
        std::optional<T> _transform{ std::nullopt };
    };

}
