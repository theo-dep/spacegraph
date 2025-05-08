#pragma once

#include <spacetree/spacetree_amalgamated.h>

#include <array>
#include <valarray>

struct StlMatrix4
{
    static constexpr std::size_t dim = 4;

    StlMatrix4()
        : StlMatrix4(0)
    {
    }

    StlMatrix4(float val)
    {
        diagonal() = val;
    }

    StlMatrix4(std::array<float, dim * dim> array)
    {
        std::copy(array.cbegin(), array.cend(), std::begin(_data));
    }

    void set_identity()
    {
        _data = 0;
        diagonal() = 1;
    }

    bool operator==(const StlMatrix4& other) const
    {
        return (_data == other._data).min();
    }

    StlMatrix4 operator*(const StlMatrix4& other) const
    {
        StlMatrix4 newer;
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

template <>
struct matrix_trait<StlMatrix4>
{
    static void set_identity(StlMatrix4& self)
    {
        self.set_identity();
    }

    static StlMatrix4 multiply(const StlMatrix4& self, const StlMatrix4& other)
    {
        return self * other;
    }
};
