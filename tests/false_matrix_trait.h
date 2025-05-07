#pragma once

#include <spacetree/spacetree.h>

#include <valarray>

using FalseMatrixTrait = std::valarray<float>;

inline FalseMatrixTrait createFalse(float val)
{
    return FalseMatrixTrait{ val, 16 };
}

template <>
struct matrix_trait<FalseMatrixTrait>
{
    static FalseMatrixTrait multiply(const FalseMatrixTrait& self, const FalseMatrixTrait& other)
    {
        return self * other;
    }
};

inline spacetree::details::Multipliable test(const spacetree::details::Multipliable& mat, const spacetree::details::Multipliable& other)
{
    return mat.multiply(other);
}
