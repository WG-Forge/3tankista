#pragma once

#include <cmath>

#include "utility/matrix.hpp"

#include "game/game_configuration.h"

class Transform
{
private:
    Matrix4f transform;

public:
    Transform();
    Transform(const Matrix4f& transform);
    Transform(const Vector2f& position_xy);
    Transform(const Vector3f& position);
    Transform(const Vector3f& position,
              const Vector3f& axis,
              const float     angle);
    Transform(const Vector3f& position,
              const Vector3f& axis,
              const float     angle,
              const Vector3f& scale);

    inline void Zero() { this->transform = Matrix4f{}; }
    inline void One()
    {
        this->transform = Matrix4f{ { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f } };
    }
    inline void Identity()
    {
        this->transform = Matrix4f{ { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f },
                                    { 1.0f, 1.0f, 1.0f, 1.0f } };
    }

    void SetPosition(const Vector3f& position);
    /*
    void SetRotation(const Vector3f& rotation_euler);
    void SetScale(const Vector3f& scale);

    inline Vector3f GetRight() const
    {
        const auto& col = this->transform.getCol(0);
        return Vector3f(col.x(), col.y(), col.z());
    }
    inline Vector3f GetUp() const
    {
        const auto& col = this->transform.getCol(1);
        return Vector3f(col.x(), col.y(), col.z());
    }
    inline Vector3f GetForward() const
    {
        // TODO: write methods to construct less size vectors from bigest
        // vectors
        const auto& col = this->transform.getCol(2);
        return Vector3f(col.x(), col.y(), col.z());
    }

    void SetRight(const Vector3f& right);
    void SetUp(const Vector3f& up);
    void SetForward(const Vector3f& forward);
*/
    inline Vector3f GetPosition() const
    {
        const auto& col = this->transform.getCol(3);
        return Vector3f(col.x(), col.y(), col.z());
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	glm::vec3 Transform::GetRotation();
    ///
    /// Summary:	Returns euler angles.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	14/10/2017
    ///
    /// Returns:	The rotation.
    ///-------------------------------------------------------------------------------------------------

    Vector3f GetRotation() const;
    /*
        Vector3f GetScale() const;
    */
    // conversion to float array
    inline operator const float*() const { return this->transform.data(); }
    inline operator const Matrix4f&() const { return this->transform; }

    inline static Transform IDENTITY() { return Transform(); }

private:
    Vector3f Hex2Pixel(const Vector3f& hex)
    {
        const auto& pixel =
            hex.x() * HEX_BASIS.getCol(0) + hex.y() * HEX_BASIS.getCol(1);
        return { pixel.x() / GAME_WINDOW_WIDTH,
                 pixel.y() / GAME_WINDOW_HEIGHT,
                 0 };
    }

}; // class Transform
