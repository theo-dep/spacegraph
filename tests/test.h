#pragma once

#include "glm_matrix_trait.h"
#include "qt_matrix_trait.h"
#include "stl_matrix_trait.h"

#include <QtGui/QTransform>

template <typename T>
T identity(float val);

template <>
inline glm::mat4 identity<glm::mat4>(float val)
{
    return glm::mat4(val);
}

template <>
inline QMatrix4x4 identity<QMatrix4x4>(float val)
{
    QMatrix4x4 mat;
    mat(0, 0) = val;
    mat(1, 1) = val;
    mat(2, 2) = val;
    mat(3, 3) = val;
    return mat;
}

template <>
inline stl::Matrix4 identity<stl::Matrix4>(float val)
{
    return stl::Matrix4(val);
}

template <typename T>
T default_value();

template <>
inline glm::mat4 default_value<glm::mat4>()
{
    return glm::mat4(
        glm::vec4(1, 0, 0, 0),
        glm::vec4(0, 2, 0, 0),
        glm::vec4(0, 0, 3, 0),
        glm::vec4(1, 2, 3, 0));
}

template <>
inline QMatrix4x4 default_value<QMatrix4x4>()
{
    return QMatrix4x4{
        std::array{
            1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            1.f, 2.f, 3.f, 0.f }
            .data()
    };
}

template <>
inline stl::Matrix4 default_value<stl::Matrix4>()
{
    return stl::Matrix4(
        std::array{
            1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            1.f, 2.f, 3.f, 0.f });
}

template <typename T>
inline auto default_param_constructor()
{
    if constexpr (std::is_same_v<T, QMatrix4x4>) {
        return QTransform{};
    } else {
        return 1.f;
    }
}
