#pragma once

#include <spacetree/spacetree.h>

#include <QtGui/QMatrix4x4>

// test without namespace
inline void set_identity(spacetree::tag_t, QMatrix4x4& self)
{
    self.setToIdentity();
}

inline QMatrix4x4 multiply(spacetree::tag_t, const QMatrix4x4& self, const QMatrix4x4& other)
{
    return self * other;
}
