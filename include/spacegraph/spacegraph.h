#pragma once

#include <concepts>
#include <functional>
#include <optional>
#include <tuple>
#include <utility>

// Must be implemented for your own matrix type
// void set_identity(spacegraph::tag_t, T& self);
// T multiply(spacegraph::tag_t, const T& self, const T& other);

namespace spacegraph
{

    struct tag_t
    {
        explicit tag_t() = default;
    };

    inline constexpr tag_t tag{};

    namespace details
    {

        template <typename T>
        concept Transformable = requires(T m) {
            { set_identity(tag, m) } -> std::same_as<void>;
            { multiply(tag, m, std::declval<T>()) } -> std::convertible_to<T>;
        };

        template <Transformable T>
        constexpr auto pointer_cast(void* ptr) { return static_cast<T*>(ptr); }

        template <Transformable T>
        constexpr auto pointer_cast(const void* ptr) { return static_cast<const T*>(ptr); }

        struct Destroy;
        struct Copy;
        struct Move;
        struct SetIdentity;
        struct Multiply;

        using TransformableVtable = std::tuple<Destroy, Copy, Move, SetIdentity, Multiply>;

        struct TransformableErasure
        {
            template <Transformable T>
            constexpr TransformableErasure(T x);

            template <Transformable T>
            constexpr TransformableErasure(std::in_place_type_t<T>);

            template <Transformable T, typename... Args>
            constexpr TransformableErasure(std::in_place_type_t<T>, Args&&... args);

            constexpr ~TransformableErasure();
            constexpr TransformableErasure(const TransformableErasure& other);
            constexpr TransformableErasure(TransformableErasure&& other);
            constexpr TransformableErasure& operator=(const TransformableErasure& other);
            constexpr TransformableErasure& operator=(TransformableErasure&& other);

            constexpr void set_identity() const;

            constexpr TransformableErasure multiply(const TransformableErasure& other) const;

            template <Transformable T>
            constexpr auto cast() const;

        private:
            std::reference_wrapper<const TransformableVtable> _vtable;
            void* _state{ nullptr };
        };

        struct Destroy
        {
            void (*function)(void*);
        };
        struct Copy
        {
            void* (*function)(const void*);
        };
        struct Move
        {
            void* (*function)(void*);
        };
        struct SetIdentity
        {
            void (*function)(void*);
        };
        struct Multiply
        {
            TransformableErasure (*function)(const void*, const void*);
        };

        template <Transformable T>
        static constexpr void set_identity(void* ptr)
        {
            set_identity(tag, *pointer_cast<T>(ptr));
        }

        template <Transformable T>
        static constexpr TransformableErasure multiply(const void* ptr, const void* other)
        {
            return TransformableErasure{ multiply(tag, *pointer_cast<T>(ptr), *pointer_cast<T>(other)) };
        }

        struct TransformableVtableFactory
        {
            template <Transformable T>
            static constexpr const TransformableVtable& get()
            {
                static constexpr TransformableVtable vtable{ make<T>() };
                return vtable;
            }

        private:
            template <Transformable T>
            static constexpr TransformableVtable make()
            {
                return { Destroy{ [](void* ptr) constexpr {
                             delete pointer_cast<T>(ptr);
                         } },
                         Copy{ [](const void* ptr) constexpr -> void* {
                             return new T(*pointer_cast<T>(ptr));
                         } },
                         Move{ [](void* ptr) constexpr -> void* {
                             return new T(std::move(*pointer_cast<T>(ptr)));
                         } },
                         SetIdentity{ set_identity<T> },
                         Multiply{ multiply<T> } };
            }
        };

        template <Transformable T>
        constexpr TransformableErasure::TransformableErasure(T x)
            : TransformableErasure(std::in_place_type<T>, std::forward<T>(x))
        {
        }

        template <Transformable T>
        constexpr TransformableErasure::TransformableErasure(std::in_place_type_t<T>)
            : TransformableErasure(T{})
        {
        }

        template <Transformable T, typename... Args>
        constexpr TransformableErasure::TransformableErasure(std::in_place_type_t<T>, Args&&... args)
            : _vtable{ TransformableVtableFactory::get<std::decay_t<T>>() }
            , _state{ new T(std::forward<Args>(args)...) }
        {
        }

        constexpr TransformableErasure::~TransformableErasure()
        {
            std::get<Destroy>(_vtable.get()).function(_state);
        }

        constexpr TransformableErasure::TransformableErasure(const TransformableErasure& other)
            : _vtable{ other._vtable }
            , _state{ std::get<Copy>(other._vtable.get()).function(other._state) }
        {
        }

        constexpr TransformableErasure::TransformableErasure(TransformableErasure&& other)
            : _vtable{ other._vtable }
            , _state{ std::get<Move>(other._vtable.get()).function(other._state) }
        {
        }

        constexpr TransformableErasure& TransformableErasure::operator=(const TransformableErasure& other)
        {
            std::get<Destroy>(_vtable.get()).function(_state);
            _vtable = other._vtable;
            _state = std::get<Copy>(other._vtable.get()).function(other._state);
            return *this;
        }

        constexpr TransformableErasure& TransformableErasure::operator=(TransformableErasure&& other)
        {
            std::get<Destroy>(_vtable.get()).function(_state);
            _vtable = other._vtable;
            _state = std::get<Move>(other._vtable.get()).function(other._state);
            return *this;
        }

        constexpr void TransformableErasure::set_identity() const
        {
            std::get<SetIdentity>(_vtable.get()).function(_state);
        }

        constexpr TransformableErasure TransformableErasure::multiply(const TransformableErasure& other) const
        {
            return std::get<Multiply>(_vtable.get()).function(_state, other._state);
        }

        template <Transformable T>
        constexpr auto TransformableErasure::cast() const
        {
            static constexpr const TransformableVtable& vtable{ TransformableVtableFactory::get<std::decay_t<T>>() };
            return std::addressof(_vtable.get()) == std::addressof(vtable)
                       ? pointer_cast<T>(std::as_const(_state))
                       : nullptr;
        }

    }

    struct Node
    {
        constexpr Node() = default;

        template <details::Transformable T>
        constexpr Node(std::in_place_type_t<T>)
            : _transform(std::in_place, std::in_place_type<T>)
        {
            _transform->set_identity();
        }

        template <details::Transformable T, typename... Args>
        constexpr Node(std::in_place_type_t<T>, Args&&... args)
            : _transform(std::in_place, std::in_place_type<T>, std::forward<Args>(args)...)
        {
        }

        template <details::Transformable T>
        constexpr Node(T x)
            : Node{ std::in_place_type<T>, std::forward<T>(x) }
        {
        }

        constexpr ~Node() = default;
        constexpr Node(const Node&) = default;
        constexpr Node(Node&&) = default;
        constexpr Node& operator=(const Node&) = default;
        constexpr Node& operator=(Node&&) = default;

        template <details::Transformable T>
        constexpr std::optional<T> transform_to(const Node& other) const
        {
            if (!_transform)
                return std::nullopt;
            if (std::addressof(other) == this)
                return *_transform->cast<T>();
            return std::nullopt;
        }

    private:
        std::optional<details::TransformableErasure> _transform{ std::nullopt };
    };

}
