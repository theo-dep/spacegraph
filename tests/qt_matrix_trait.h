#pragma once

#include <spacegraph/spacegraph.h>

#include <QtGui/QMatrix4x4>

// test without namespace
inline void set_identity(spacegraph::tag_t, QMatrix4x4& self)
{
    self.setToIdentity();
}

inline QMatrix4x4 multiply(spacegraph::tag_t, const QMatrix4x4& self, const QMatrix4x4& other)
{
    return self * other;
}
