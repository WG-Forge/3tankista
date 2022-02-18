#pragma once

#include "matrix.hpp"

namespace myMath
{

template <typename T>
Matrix4<T> translate(const Matrix4<T>& m, const Vector3<T> v)
{
    Matrix4<T>  result{ m };
    const auto& newPos = m.getCol(0) * v[0] + m.getCol(1) * v[1] +
                         m.getCol(2) * v[2] + m.getCol(3);
    result.replaceCol(3, newPos);
    return result;
}

template <typename T>
Matrix4<T> rotate(const Matrix4<T>& m, T angle, const Vector3<T> v)
{
    const T a = angle;
    const T c = std::cos(a);
    const T s = std::cos(a);

    Vector3<T> axis{ v.getNormalized() };
    Vector3<T> tmp{ (T(1) - c) * axis };

    Matrix4<T> rotate;
    rotate.getCol(0)[0] = c + tmp[0] * axis[0];
    rotate.getCol(0)[1] = tmp[0] * axis[1] + s * axis[2];
    rotate.getCol(0)[2] = tmp[0] * axis[2] - s * axis[1];

    rotate.getCol(1)[0] = tmp[1] * axis[0] - s * axis[2];
    rotate.getCol(1)[1] = c + tmp[1] * axis[1];
    rotate.getCol(1)[2] = tmp[1] * axis[2] + s * axis[0];

    rotate.getCol(2)[0] = tmp[2] * axis[0] + s * axis[1];
    rotate.getCol(2)[1] = tmp[2] * axis[1] - s * axis[0];
    rotate.getCol(2)[2] = c + tmp[2] * axis[2];

    Matrix4<T> result;
    result.replaceCol(0,
                      m.getCol(0) * rotate.getCol(0)[0] +
                          m.getCol(1) * rotate.getCol(0)[1] +
                          m.getCol(2) * rotate.getCol(0)[2]);
    result.replaceCol(1,
                      m.getCol(0) * rotate.getCol(1)[0] +
                          m.getCol(1) * rotate.getCol(1)[1] +
                          m.getCol(2) * rotate.getCol(1)[2]);
    result.replaceCol(2,
                      m.getCol(0) * rotate.getCol(2)[0] +
                          m.getCol(1) * rotate.getCol(2)[1] +
                          m.getCol(2) * rotate.getCol(2)[2]);
    result.replaceCol(3, m.getCol(3));
    return result;
}

template <typename T>
Matrix4<T> scale(const Matrix4<T>& m, const Vector3<T>& v)
{
    Matrix4<T> result;
    result.replaceCol(0, m.getCol(0) * v[0]);
    result.replaceCol(1, m.getCol(1) * v[1]);
    result.replaceCol(2, m.getCol(2) * v[2]);
    result.replaceCol(3, m.getCol(3));
    return result;
}

} // namespace myMath
