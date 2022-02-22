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
