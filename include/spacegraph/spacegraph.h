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

    static constexpr tag_t tag{};

    namespace details
    {

        template <typename T>
        class optional_view
        {
        private:
            T* _value{ nullptr };

        public:
            using value_type = T;

            constexpr optional_view(T& value)
                : _value{ std::addressof(value) }
            {
            }

            constexpr optional_view(std::nullopt_t)
                : _value{ nullptr }
            {
            }

            template <typename U>
                requires std::is_convertible_v<U*, T*> || std::is_same_v<U, T>
            constexpr optional_view(const optional_view<U>& other)
                : _value{ other._value }
            {
            }

            constexpr ~optional_view() = default;

            constexpr optional_view(T&&) = delete;
            constexpr optional_view(std::nullptr_t) = delete;
            constexpr optional_view(optional_view<T>&&) = delete;
            constexpr optional_view<T>& operator=(const optional_view<T>&) = delete;
            constexpr optional_view<T>& operator=(optional_view<T>&&) = delete;

            constexpr T* operator->() { return _value; }
            constexpr const T* operator->() const { return _value; }

            constexpr T& operator*() { return *_value; }
            constexpr const T& operator*() const { return *_value; }

            constexpr T& value() { return *_value; }
            constexpr const T& value() const { return *_value; }

            constexpr bool has_value() const { return _value; }
            constexpr operator bool() const { return _value; }

            constexpr void reset() noexcept { _value = nullptr; }
        };

        template <typename T>
        concept Transformable = requires(T m) {
            { set_identity(tag, m) } -> std::same_as<void>;
            { multiply(tag, m, std::declval<T>()) } -> std::convertible_to<T>;
        };

        template <Transformable T>
        constexpr T& pointer_cast(void* ptr) { return *static_cast<T*>(ptr); }

        template <Transformable T>
        constexpr const T& pointer_cast(const void* ptr) { return *static_cast<const T*>(ptr); }

        struct TransformableVtable;

        class TransformableErasure
        {
        private:
            std::reference_wrapper<const TransformableVtable> _vtable;
            void* _state{ nullptr };

        public:
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
            constexpr optional_view<const T> cast() const;
        };

        struct TransformableVtable
        {
            void (*destroy)(void*);
            void* (*copy)(const void*);
            void* (*move)(void*);
            void (*set_identity)(void*);
            TransformableErasure (*multiply)(const void*, const void*);
        };

        template <Transformable T>
        static constexpr void set_identity(void* ptr)
        {
            set_identity(tag, pointer_cast<T>(ptr));
        }

        template <Transformable T>
        static constexpr TransformableErasure multiply(const void* ptr, const void* other)
        {
            return TransformableErasure{ multiply(tag, pointer_cast<T>(ptr), pointer_cast<T>(other)) };
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
                return {
                    .destroy{ [](void* ptr) constexpr {
                        delete std::addressof(pointer_cast<T>(ptr));
                    } },
                    .copy{ [](const void* ptr) constexpr -> void* {
                        return new T(pointer_cast<T>(ptr));
                    } },
                    .move{ [](void* ptr) constexpr -> void* {
                        return new T(std::move(pointer_cast<T>(ptr)));
                    } },
                    .set_identity{ set_identity<T> },
                    .multiply{ multiply<T> }
                };
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
            _vtable.get().destroy(_state);
        }

        constexpr TransformableErasure::TransformableErasure(const TransformableErasure& other)
            : _vtable{ other._vtable }
            , _state{ other._vtable.get().copy(other._state) }
        {
        }

        constexpr TransformableErasure::TransformableErasure(TransformableErasure&& other)
            : _vtable{ other._vtable }
            , _state{ other._vtable.get().move(other._state) }
        {
        }

        constexpr TransformableErasure& TransformableErasure::operator=(const TransformableErasure& other)
        {
            _vtable.get().destroy(_state);
            _vtable = other._vtable;
            _state = other._vtable.get().copy(other._state);
            return *this;
        }

        constexpr TransformableErasure& TransformableErasure::operator=(TransformableErasure&& other)
        {
            _vtable.get().destroy(_state);
            _vtable = other._vtable;
            _state = other._vtable.get().move(other._state);
            return *this;
        }

        constexpr void TransformableErasure::set_identity() const
        {
            _vtable.get().set_identity(_state);
        }

        constexpr TransformableErasure TransformableErasure::multiply(const TransformableErasure& other) const
        {
            return _vtable.get().multiply(_state, other._state);
        }

        template <Transformable T>
        constexpr optional_view<const T> TransformableErasure::cast() const
        {
            static constexpr const TransformableVtable& vtable{ TransformableVtableFactory::get<std::decay_t<T>>() };
            if (std::addressof(_vtable.get()) == std::addressof(vtable))
                return pointer_cast<T>(std::as_const(_state));
            return std::nullopt;
        }

    }

    class Node
    {
    private:
        std::optional<details::TransformableErasure> _transform{ std::nullopt };

    public:
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
        constexpr details::optional_view<const T> transformable() const
        {
            return _transform->cast<T>();
        }

        template <details::Transformable T>
        constexpr details::optional_view<const T> transform_to(const Node& other) const
        {
            if (!_transform)
                return std::nullopt;
            if (std::addressof(other) == this)
                return transformable<T>();
            return std::nullopt;
        }
    };

}
