#include "stl_matrix_trait.h"
#include "test_transform_node.h"

stl::Matrix4 identity()
{
    return stl::Matrix4(1);
}

stl::Matrix4 default_value()
{
    return stl::Matrix4(std::array{ 1.f, 0.f, 0.f, 0.f,
                                    0.f, 2.f, 0.f, 0.f,
                                    0.f, 0.f, 3.f, 0.f,
                                    1.f, 2.f, 3.f, 0.f });
}
