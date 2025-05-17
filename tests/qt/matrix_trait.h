#pragma once

#include <QtGui/QMatrix4x4>

namespace spacetree
{
    struct tag_t;
}

// test without namespace
void set_identity(spacetree::tag_t, QMatrix4x4& self);
QMatrix4x4 multiply(spacetree::tag_t, const QMatrix4x4& self, const QMatrix4x4& other);

#include <spacetree/spacetree.h>

inline void set_identity(spacetree::tag_t, QMatrix4x4& self)
{
    self.setToIdentity();
}

inline QMatrix4x4 multiply(spacetree::tag_t, const QMatrix4x4& self, const QMatrix4x4& other)
{
    return self * other;
}
