#include <erased/erased.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <print>

struct Multiply;
using Multipliable = erased::erased<Multiply, erased::Copy, erased::Move>;

Multipliable multiply(const glm::mat4& self, const Multipliable& other);

struct Multiply {
    constexpr static Multipliable invoker(const auto& self, const Multipliable& other) {
        return ::multiply(self, other);
    }

    constexpr Multipliable multiply(this const auto &erased, const Multipliable& other) {
        return erased.invoke(Multiply{}, other);
    }
};

Multipliable test(const Multipliable& mat, const Multipliable& other) {
    return mat.multiply(other);
}

Multipliable multiply(const glm::mat4& self, const Multipliable& other)
{
    try {
        return glm::matrixCompMult(self, erased::any_cast<glm::mat4>(other));
    } catch (std::bad_cast) {
        return glm::mat4(0);
    }
}

int main()
{
    glm::mat4 mat1(2), mat2(3);
    Multipliable res = test(mat1, mat2);

    assert(erased::is<glm::mat4>(res));

    std::println("{}", glm::to_string(erased::any_cast<glm::mat4>(res)));

    return 0;
}
