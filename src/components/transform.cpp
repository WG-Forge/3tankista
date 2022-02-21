#include "transform.h"

#include "utility/matrix_transform.h"

Transform::Transform()
    : transform{
        { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }
    }
{
}

Transform::Transform(const Matrix4f& transform)
    : transform(transform)
{
}

Transform::Transform(const Vector3i& position)
{
    this->transform = myMath::translate(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.0f },
                                                  { 0.0f, 1.0f, 0.0f, 0.0f },
                                                  { 0.0f, 0.0f, 1.0f, 0.0f },
                                                  { 0.0f, 0.0f, 0.0f, 1.0f } },
                                        Hex2Pixel(position));
}

Transform::Transform(const Vector2i& position_xy)
{
    this->transform = myMath::translate(
        Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 1.0f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, 1.0f, 0.0f },
                  { 0.0f, 0.0f, 0.0f, 1.0f } },
        Hex2Pixel(Vector3i(position_xy.x(), position_xy.y(), 0 /*-position_xy.x() - position_xy.y()*/)));
}

Transform::Transform(const Vector3i& position, const Vector3f& axis, const float angle_radians)
{
    Matrix4f P  = myMath::translate(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.0f },
                                             { 0.0f, 1.0f, 0.0f, 0.0f },
                                             { 0.0f, 0.0f, 1.0f, 0.0f },
                                             { 0.0f, 0.0f, 0.0f, 1.0f } },
                                   Hex2Pixel(position));
    Matrix4f PR = myMath::rotate(P, angle_radians, axis);

    this->transform = PR;
}

Transform::Transform(const Vector3i& position, const Vector3f& axis, const float angle_radians, const Vector3f& scale)
{
    Matrix4f P   = myMath::translate(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.0f },
                                             { 0.0f, 1.0f, 0.0f, 0.0f },
                                             { 0.0f, 0.0f, 1.0f, 0.0f },
                                             { 0.0f, 0.0f, 0.0f, 1.0f } },
                                   Hex2Pixel(position));
    Matrix4f PR  = myMath::rotate(P, angle_radians, axis);
    Matrix4f PRS = myMath::scale(PR, scale);

    this->transform = PRS;
}

void Transform::SetPosition(const Vector3i& position)
{
    const auto& pixel = Hex2Pixel(position);
    this->transform.replaceCol(3, Vector4f(pixel.x(), pixel.y(), pixel.z(), this->transform.getCol(3).w()));
}
/*
void Transform::SetRotation(const Vector3f& rotation_euler_radians)
{
    Vector3f Tr = this->GetPosition();
    Vector3f Sc = this->GetScale();

    auto T = myMath::translate(Matrix4f{ { 1.0f, 1.0f, 1.0f, 1.0f },
                                         { 1.0f, 1.0f, 1.0f, 1.0f },
                                         { 1.0f, 1.0f, 1.0f, 1.0f },
                                         { 1.0f, 1.0f, 1.0f, 1.0f } },
                               Tr);
    auto R = yawPitchRoll(rotation_euler_radians.x,
                          rotation_euler_radians.y,
                          rotation_euler_radians.z);

    this->transform = T * R * myMath::scale(Sc);
}

void Transform::SetScale(const Vector3f& scale)
{
    Vector3f Tr = this->GetPosition();
    Vector3f Or = this->GetRotation();

    auto T = myMath::translate(Matrix4f(1.0f), Tr);
    auto R = yawPitchRoll(Or.x, Or.y, Or.z);

    this->transform = T * R * myMath::scale(scale);
}

void Transform::SetRight(const Vector3f& right)
{
    this->transform.replaceCol(
        0,
        Vector4f(
            right.x(), right.y(), right.z(), this->transform.getCol(0).w()));
}

void Transform::SetUp(const Vector3f& up)
{
    this->transform.replaceCol(
        1, Vector4f(up.x(), up.y(), up.z(), this->transform.getCol(1).w()));
}

void Transform::SetForward(const Vector3f& forward)
{
    this->transform.replaceCol(2,
                               Vector4f(forward.x(),
                                        forward.y(),
                                        forward.z(),
                                        this->transform.getCol(2).w()));
}

Vector3f Transform::GetRotation() const
{
    Vector3f euler_angles;
    extractEulerAngleXYZ(
        this->transform, euler_angles[0], euler_angles[1], euler_angles[2]);

    return euler_angles;
}

Vector3f Transform::GetScale() const
{
    Vector3f row[3];
    for (size_t i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            row[i][j] = this->transform.getCol(i)[j];

    return Vector3f(length(row[0]), length(row[1]), length(row[1]));
}
*/
