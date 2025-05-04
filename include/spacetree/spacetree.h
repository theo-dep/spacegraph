#pragma once

#include <erased/erased.h>

struct Multiply;
using Multipliable = erased::erased<Multiply, erased::Copy, erased::Move>;

template <typename T>
struct matrix_trait
{
    static_assert(false, "Must be implemented for your own matrix type");
    static T multiply(const T& self, const T& other);
};

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
