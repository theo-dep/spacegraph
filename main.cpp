#include <erased/erased.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QtCore/QDebug>
#include <QtGui/QMatrix4x4>

#include <print>

struct Multiply;
using Multipliable = erased::erased<Multiply, erased::Copy, erased::Move>;

template <typename T>
struct matrix_trait
{
    static_assert(false, "Must be implemented for your own matrix type");
    static T multiply(const T& self, const T& other);
    static T type_error();
};

struct Multiply
{
    constexpr static Multipliable invoker(const auto& self, const Multipliable& other)
    {
        using SelfType = std::remove_cvref_t<decltype(self)>;
        if (erased::is<SelfType>(other))
            return matrix_trait<SelfType>::multiply(self, erased::any_cast<SelfType>(other));
        return matrix_trait<SelfType>::type_error();
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
struct matrix_trait<glm::mat4>
{
    static glm::mat4 multiply(const glm::mat4& self, const glm::mat4& other)
    {
        return glm::matrixCompMult(self, other);
    }

    static glm::mat4 type_error()
    {
        return glm::mat4(0);
    }
};

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
struct matrix_trait<QMatrix4x4>
{
    static QMatrix4x4 multiply(const QMatrix4x4& self, const QMatrix4x4& other)
    {
        return self * other;
    }

    static QMatrix4x4 type_error()
    {
        return create(0);
    }
};

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
