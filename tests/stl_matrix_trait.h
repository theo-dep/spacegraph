#pragma once

#include <algorithm>
#include <array>
#include <functional>
#ifdef __cpp_lib_mdspan
#include <mdspan>
namespace std_mdspan = std;
#else
#include <experimental/mdspan>
namespace std_mdspan = std::experimental;
#endif

namespace stl
{
    template <typename T, std::size_t N>
    struct Matrix
    {
        constexpr Matrix() = default;

        constexpr Matrix(T val)
        {
            set_diagonal(val);
        }

        constexpr Matrix(std::array<T, N * N> array)
            : _data{ array }
            , _data_view{ _data.data(), N, N }
        {
        }

        constexpr Matrix(const Matrix& other)
            : _data{ other._data }
            , _data_view{ _data.data(), N, N }
        {
        }

        constexpr Matrix(Matrix&& other)
            : _data{ std::move(other._data) }
            , _data_view{ _data.data(), N, N }
        {
        }

        constexpr void set_identity()
        {
            set_diagonal(1);
        }

        constexpr Matrix operator*(const Matrix& other) const
        {
            std::array<T, N * N> array;
            std::ranges::transform(_data, other._data, array.begin(), std::multiplies{});
            return array;
        }

        constexpr bool operator==(const Matrix& other) const
        {
            return _data == other._data;
        }

        constexpr Matrix& operator=(const Matrix& other)
        {
            _data = other._data;
            _data_view = decltype(_data_view)(_data.data(), N, N);
            return *this;
        }

        constexpr Matrix& operator=(Matrix&& other) noexcept
        {
            _data = std::move(other._data);
            _data_view = decltype(_data_view)(_data.data(), N, N);
            return *this;
        }

    protected:
        template <typename U, std::size_t M>
        friend std::ostream& operator<<(std::ostream& stream, const Matrix<U, M>& mat);

        constexpr void set_diagonal(float val)
        {
            for (auto i{ 0uz }; i < N; ++i) {
                _data_view[i, i] = val;
            }
        }

    private:
        std::array<T, N * N> _data{ 0 };
        std_mdspan::mdspan<T, std_mdspan::dextents<std::size_t, 2>> _data_view{ _data.data(), N, N };
    };

    template <typename U, std::size_t M>
    inline std::ostream& operator<<(std::ostream& stream, const Matrix<U, M>& mat)
    {
        std::ranges::copy(mat._data, std::ostream_iterator<U>(stream, " "));
        return stream;
    }

    using Matrix4 = Matrix<float, 4>;
}

#include <spacegraph/spacegraph.h>

// test inside custom namespace and templated
namespace stl
{
    template <typename T, std::size_t N>
    inline void set_identity(::spacegraph::tag_t, Matrix<T, N>& self)
    {
        self.set_identity();
    }

    template <typename T, std::size_t N>
    inline Matrix<T, N> multiply(::spacegraph::tag_t, const Matrix<T, N>& self, const Matrix<T, N>& other)
    {
        return self * other;
    }
}
