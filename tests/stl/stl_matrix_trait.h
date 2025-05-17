#pragma once

#include <array>
#include <valarray>

namespace stl
{
    struct Matrix4
    {
        static constexpr std::size_t dim = 4;

        Matrix4()
            : Matrix4(0)
        {
        }

        Matrix4(float val)
        {
            diagonal() = val;
        }

        Matrix4(std::array<float, dim * dim> array)
        {
            std::copy(array.cbegin(), array.cend(), std::begin(_data));
        }

        void set_identity()
        {
            _data = 0;
            diagonal() = 1;
        }

        bool operator==(const Matrix4& other) const
        {
            return (_data == other._data).min();
        }

        Matrix4 operator*(const Matrix4& other) const
        {
            Matrix4 newer;
            newer._data = _data * other._data;
            return newer;
        }

        std::slice_array<float> diagonal()
        {
            return _data[std::slice(0, dim, dim + 1)];
        }

    private:
        std::valarray<float> _data{ std::valarray<float>(dim * dim) };
    };
}

namespace spacetree
{
    struct tag_t;
}

// test inside custom namespace
namespace stl
{
    void set_identity(::spacetree::tag_t, Matrix4& self);
    Matrix4 multiply(::spacetree::tag_t, const Matrix4& self, const Matrix4& other);
}

#include <spacetree/spacetree.h>

namespace stl
{
    inline void set_identity(::spacetree::tag_t, Matrix4& self)
    {
        self.set_identity();
    }

    inline Matrix4 multiply(::spacetree::tag_t, const Matrix4& self, const Matrix4& other)
    {
        return self * other;
    }
}
