#pragma once

#include <spacetree/spacetree.h>

#include <QtGui/QMatrix4x4>

template <>
struct matrix_trait<QMatrix4x4>
{
    static QMatrix4x4 multiply(const QMatrix4x4& self, const QMatrix4x4& other)
    {
        return self * other;
    }
};
