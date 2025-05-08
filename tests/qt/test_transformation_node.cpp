#include "qt/matrix_trait.h"
#include "test_transform_node.h"

QMatrix4x4 identity()
{
    return QMatrix4x4();
}

QMatrix4x4 default_value()
{
    return QMatrix4x4{
        std::array<float, 16>{
            1, 0, 0, 1,
            0, 2, 0, 2,
            0, 0, 3, 3,
            0, 0, 0, 0 }
            .data()
    };
}
