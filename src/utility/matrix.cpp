#include "matrix.hpp"

template <>
const Matrix2f Matrix2f::getInversed() const
{
    const Matrix2f& self = *this;

    Matrix2f res;
    double   invDet = 1.0 / this->det();
    res(0, 0)       = invDet * self(1, 1);
    res(0, 1)       = -invDet * self(0, 1);
    res(1, 0)       = -invDet * self(1, 0);
    res(1, 1)       = invDet * self(0, 0);

    return res;
}

template <>
const Matrix2d Matrix2d::getInversed() const
{
    const Matrix2d& self = *this;

    Matrix2d res;
    double   invDet = 1.0 / this->det();
    res(0, 0)       = invDet * self(1, 1);
    res(0, 1)       = -invDet * self(0, 1);
    res(1, 0)       = -invDet * self(1, 0);
    res(1, 1)       = invDet * self(0, 0);

    return res;
}

template <>
const Matrix3d Matrix3d::getInversed() const
{
    const Matrix3d& self = *this;

    Matrix3d res;
    double   invDet = 1.0 / this->det();

    res(0, 0) = invDet * (self(1, 1) * self(2, 2) - self(1, 2) * self(2, 1));
    res(1, 0) = -invDet * (self(1, 0) * self(2, 2) - self(1, 2) * self(2, 0));
    res(2, 0) = invDet * (self(1, 0) * self(2, 1) - self(1, 1) * self(2, 0));

    res(0, 1) = -invDet * (self(0, 1) * self(2, 2) - self(0, 2) * self(2, 1));
    res(1, 1) = invDet * (self(0, 0) * self(2, 2) - self(0, 2) * self(2, 0));
    res(2, 1) = -invDet * (self(0, 0) * self(2, 1) - self(0, 1) * self(2, 0));

    res(0, 2) = invDet * (self(0, 1) * self(1, 2) - self(0, 2) * self(1, 1));
    res(1, 2) = -invDet * (self(0, 0) * self(1, 2) - self(0, 2) * self(1, 0));
    res(2, 2) = invDet * (self(0, 0) * self(1, 1) - self(0, 1) * self(1, 0));

    return res;
}

template <>
const Matrix4d Matrix4d::getInversed() const
{
    const Matrix4d& self = *this;

    Matrix4d res;
    double   invDet = 1.0 / this->det();

    res(0, 0) = invDet * Matrix3d({ { self(1, 1), self(1, 2), self(1, 3) },
                                    { self(2, 1), self(2, 2), self(2, 3) },
                                    { self(3, 1), self(3, 2), self(3, 3) } })
                             .det();
    res(0, 1) = -invDet * Matrix3d({ { self(0, 1), self(0, 2), self(0, 3) },
                                     { self(2, 1), self(2, 2), self(2, 3) },
                                     { self(3, 1), self(3, 2), self(3, 3) } })
                              .det();
    res(0, 2) = invDet * Matrix3d({ { self(0, 1), self(0, 2), self(0, 3) },
                                    { self(1, 1), self(1, 2), self(1, 3) },
                                    { self(3, 1), self(3, 2), self(3, 3) } })
                             .det();
    res(0, 3) = -invDet * Matrix3d({ { self(0, 1), self(0, 2), self(0, 3) },
                                     { self(1, 1), self(1, 2), self(1, 3) },
                                     { self(2, 1), self(2, 2), self(2, 3) } })
                              .det();

    res(1, 0) = -invDet * Matrix3d({ { self(1, 0), self(1, 2), self(1, 3) },
                                     { self(2, 0), self(2, 2), self(2, 3) },
                                     { self(3, 0), self(3, 2), self(3, 3) } })
                              .det();
    res(1, 1) = invDet * Matrix3d({ { self(0, 0), self(0, 2), self(0, 3) },
                                    { self(1, 0), self(1, 2), self(1, 3) },
                                    { self(3, 0), self(3, 2), self(3, 3) } })
                             .det();
    res(1, 2) = -invDet * Matrix3d({ { self(0, 0), self(0, 2), self(0, 3) },
                                     { self(2, 0), self(2, 2), self(2, 3) },
                                     { self(3, 0), self(3, 2), self(3, 3) } })
                              .det();
    res(1, 3) = invDet * Matrix3d({ { self(0, 0), self(0, 2), self(0, 3) },
                                    { self(1, 0), self(1, 2), self(1, 3) },
                                    { self(2, 0), self(2, 2), self(2, 3) } })
                             .det();

    res(2, 0) = invDet * Matrix3d({ { self(1, 0), self(1, 1), self(1, 3) },
                                    { self(2, 0), self(2, 1), self(2, 3) },
                                    { self(3, 0), self(3, 1), self(3, 3) } })
                             .det();
    res(2, 1) = -invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 3) },
                                     { self(2, 0), self(2, 1), self(2, 3) },
                                     { self(3, 0), self(3, 1), self(3, 3) } })
                              .det();
    res(2, 2) = invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 3) },
                                    { self(1, 0), self(1, 1), self(1, 3) },
                                    { self(3, 0), self(3, 1), self(3, 3) } })
                             .det();
    res(2, 3) = -invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 3) },
                                     { self(1, 0), self(1, 1), self(1, 3) },
                                     { self(2, 0), self(2, 1), self(2, 3) } })
                              .det();

    res(3, 0) = -invDet * Matrix3d({ { self(1, 0), self(1, 1), self(1, 2) },
                                     { self(2, 0), self(2, 1), self(2, 2) },
                                     { self(3, 0), self(3, 1), self(3, 2) } })
                              .det();
    res(3, 1) = invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 2) },
                                    { self(2, 0), self(2, 1), self(2, 2) },
                                    { self(3, 0), self(3, 1), self(3, 2) } })
                             .det();
    res(3, 2) = -invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 2) },
                                     { self(1, 0), self(1, 1), self(1, 2) },
                                     { self(3, 0), self(3, 1), self(3, 2) } })
                              .det();
    res(3, 3) = invDet * Matrix3d({ { self(0, 0), self(0, 1), self(0, 2) },
                                    { self(1, 0), self(1, 1), self(1, 2) },
                                    { self(2, 0), self(2, 1), self(2, 2) } })
                             .det();
    return res;
}

template <>
double Matrix2f::det() const
{
    const Matrix2f& self = *this;
    double          det  = self(0, 0) * self(1, 1) - self(0, 1) * self(1, 0);
    return det;
}

template <>
double Matrix2d::det() const
{
    const Matrix2d& self = *this;
    double          det  = self(0, 0) * self(1, 1) - self(0, 1) * self(1, 0);
    return det;
}

template <>
double Matrix3d::det() const
{
    const Matrix3d& self = *this;

    double det = self(0, 0) * Matrix2d({ { self(1, 1), self(1, 2) }, { self(2, 1), self(2, 2) } }).det() -
                 self(0, 1) * Matrix2d({ { self(1, 0), self(1, 2) }, { self(2, 0), self(2, 2) } }).det() +
                 self(0, 2) * Matrix2d({ { self(1, 0), self(1, 1) }, { self(2, 0), self(2, 1) } }).det();
    return det;
}

template <>
double Matrix4d::det() const
{
    const Matrix4d& self = *this;
    double          det  = self(0, 0) * Matrix3d({ { self(1, 1), self(1, 2), self(1, 3) },
                                         { self(2, 1), self(2, 2), self(2, 3) },
                                         { self(3, 1), self(3, 2), self(3, 3) } })
                                  .det() -
                 self(0, 1) * Matrix3d({ { self(1, 0), self(1, 2), self(1, 3) },
                                         { self(2, 0), self(2, 2), self(2, 3) },
                                         { self(3, 0), self(3, 2), self(3, 3) } })
                                  .det() +
                 self(0, 2) * Matrix3d({ { self(1, 0), self(1, 1), self(1, 3) },
                                         { self(2, 0), self(2, 1), self(2, 3) },
                                         { self(3, 0), self(3, 1), self(3, 3) } })
                                  .det() -
                 self(0, 3) * Matrix3d({ { self(1, 0), self(1, 1), self(1, 2) },
                                         { self(2, 0), self(2, 1), self(2, 2) },
                                         { self(3, 0), self(3, 1), self(3, 2) } })
                                  .det();
    return det;
}

template <>
Vector3d Vector3d::cross(const Vector3d& other) const
{
    return Vector3d{ this->y() * other.z() - this->z() * other.y(),
                     -this->x() * other.z() + this->z() * other.x(),
                     this->x() * other.y() - this->y() * other.x() };
}

template <>
RowVector3d RowVector3d::cross(const RowVector3d& other) const
{
    return RowVector3d{ this->y() * other.z() - this->z() * other.y(),
                        -this->x() * other.z() + this->z() * other.x(),
                        this->x() * other.y() - this->y() * other.x() };
}

template <>
double Vector2d::dot(const Vector2d& other) const
{
    return (this->x() * other.x() + this->y() * other.y());
}

template <>
double Vector3d::dot(const Vector3d& other) const
{
    return (this->x() * other.x() + this->y() * other.y() + this->z() * other.z());
}

template <>
double Vector4d::dot(const Vector4d& other) const
{
    return (this->x() * other.x() + this->y() * other.y() + this->z() * other.z() + this->w() * other.w());
}

template <>
double RowVector2d::dot(const RowVector2d& other) const
{
    return (this->x() * other.x() + this->y() * other.y());
}

template <>
double RowVector3d::dot(const RowVector3d& other) const
{
    return (this->x() * other.x() + this->y() * other.y() + this->z() * other.z());
}

template <>
double RowVector4d::dot(const RowVector4d& other) const
{
    return (this->x() * other.x() + this->y() * other.y() + this->z() * other.z() + this->w() * other.w());
}

void to_json(nlohmann::json& json, const Vector3i& vector3i)
{
    json = nlohmann::json{ { "x", vector3i.x() }, { "y", vector3i.y() }, { "z", vector3i.z() } };
}

void from_json(const nlohmann::json& json, Vector3i& vector3i)
{
    json.at("x").get_to(vector3i.x());
    json.at("y").get_to(vector3i.y());
    json.at("z").get_to(vector3i.z());
}
