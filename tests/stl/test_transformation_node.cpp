#include "stl_matrix_trait.h"
#include "test_transform_node.h"

StlMatrix4 identity()
{
    return StlMatrix4(1);
}

StlMatrix4 default_value()
{
    return StlMatrix4(std::array{ 1.f, 0.f, 0.f, 0.f,
                                  0.f, 2.f, 0.f, 0.f,
                                  0.f, 0.f, 3.f, 0.f,
                                  1.f, 2.f, 3.f, 0.f });
}
