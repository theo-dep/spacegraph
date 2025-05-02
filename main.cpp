#include <erased/erased.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QtCore/QDebug>
#include <QtGui/QMatrix4x4>

#include <print>

struct Multiply;
using Multipliable = erased::erased<Multiply, erased::Copy, erased::Move>;

template <typename T>
Multipliable multiply(const T& self, const Multipliable& other);

struct Multiply
{
    constexpr static Multipliable invoker(const auto& self, const Multipliable& other)
    {
        return ::multiply(self, other);
    }

    constexpr Multipliable multiply(this const auto& erased, const Multipliable& other)
    {
        return erased.invoke(Multiply{}, other);
    }
};

Multipliable test(const Multipliable& mat, const Multipliable& other)
{
    return mat.multiply(other);
}

template <>
Multipliable multiply<glm::mat4>(const glm::mat4& self, const Multipliable& other)
{
    try {
        return glm::matrixCompMult(self, erased::any_cast<glm::mat4>(other));
    } catch (std::bad_cast) {
        return glm::mat4(0);
    }
}

QMatrix4x4 create(float val)
{
    QMatrix4x4 mat;
    mat(0, 0) = val;
    mat(1, 1) = val;
    mat(2, 2) = val;
    mat(3, 3) = val;
    return mat;
}

template <>
Multipliable multiply<QMatrix4x4>(const QMatrix4x4& self, const Multipliable& other)
{
    try {
        return self * erased::any_cast<QMatrix4x4>(other);
    } catch (std::bad_cast) {
        return create(0);
    }
}

int main()
{
    glm::mat4 matGlm1(2), matGlm2(3);
    Multipliable resGlm = test(matGlm1, matGlm2);
    assert(erased::is<glm::mat4>(resGlm));
    std::println("glm: {}", glm::to_string(erased::any_cast<glm::mat4>(resGlm)));

    QMatrix4x4 matQt1(create(2)), matQt2(create(3));
    Multipliable resQt = test(matQt1, matQt2);
    assert(erased::is<QMatrix4x4>(resQt));
    std::println("qt: {}", QDebug::toString(erased::any_cast<QMatrix4x4>(resQt)).toStdString());

    Multipliable resGlmFalse = test(matGlm1, matQt2);
    assert(erased::is<glm::mat4>(resGlmFalse));
    std::println("glm x qt: {}", glm::to_string(erased::any_cast<glm::mat4>(resGlmFalse)));

    Multipliable resQtFalse = test(matQt1, matGlm2);
    assert(erased::is<QMatrix4x4>(resQtFalse));
    std::println("qt x glm: {}", QDebug::toString(erased::any_cast<QMatrix4x4>(resQtFalse)).toStdString());

    return 0;
}
