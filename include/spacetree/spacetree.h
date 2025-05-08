#pragma once

#include <erased/erased.h>

#include <optional>
#include <variant>

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

    struct Node
    {
        constexpr Node() = default;

        template <typename T, typename... Args>
        constexpr Node(std::in_place_type_t<T>, Args&&... args)
            : _transform(std::in_place_type<details::Transformable>, std::in_place_type<T>, std::forward<Args>(args)...)
        {
            transformable().set_identity();
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

        constexpr std::optional<details::Transformable> transform_to(const Node& other) const
        {
            if (_transform.index() == monostate_index)
                return std::nullopt;
            if (std::addressof(other) == this)
                return transformable();
            return std::nullopt;
        }

    protected:
        constexpr details::Transformable& transformable() { return std::get<details::Transformable>(_transform); }
        constexpr const details::Transformable& transformable() const { return std::get<details::Transformable>(_transform); }

    private:
        static constexpr std::size_t monostate_index{ 0 };
        std::variant<std::monostate, details::Transformable> _transform;
    };

}
