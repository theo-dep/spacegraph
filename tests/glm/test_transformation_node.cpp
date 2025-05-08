#include "glm/matrix_trait.h"
#include "test_transform_node.h"

glm::mat4 identity()
{
    return glm::mat4(1);
}

glm::mat4 default_value()
{
    return glm::mat4(glm::vec4(1, 0, 0, 0),
                     glm::vec4(0, 2, 0, 0),
                     glm::vec4(0, 0, 3, 0),
                     glm::vec4(1, 2, 3, 0));
}
