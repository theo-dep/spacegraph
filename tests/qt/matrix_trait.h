#pragma once

#include <spacetree/spacetree_amalgamated.h>

#include <QtGui/QMatrix4x4>

template <>
struct matrix_trait<QMatrix4x4>
{
    static void set_identity(QMatrix4x4& self)
    {
        self.setToIdentity();
    }

    static QMatrix4x4 multiply(const QMatrix4x4& self, const QMatrix4x4& other)
    {
        return self * other;
    }
};
