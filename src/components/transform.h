#pragma once

#include <cmath>

#include "utility/matrix.hpp"

#include "game/game_configuration.h"

// TODO: Add operator=
class Transform
{
private:
    Matrix4f transform;

public:
    Transform();
    explicit Transform(const Matrix4f& transform);
    explicit Transform(const Vector2i& position_xy);
    explicit Transform(const Vector3i& position);
    Transform(const Vector3i& position, const Vector3f& axis, float angle);
    Transform(const Vector3i& position, const Vector3f& axis, float angle, const Vector3f& scaleFactors);

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

    void SetScale(const Vector3f& scale)
    {
        this->transform(0, 0) = scale.x();
        this->transform(1, 1) = scale.y();
        this->transform(2, 2) = scale.z();
    }

    void SetPosition(const Vector3f& position);
    void SetPosition(const Vector3i& position);

    inline Vector3i GetPosition() const
    {
        const auto& col = this->transform.getCol(3);
        return Pixel2Hex(Vector3f{ col.x(), col.y(), col.z() });
    }

    // conversion to float array
    inline operator const float*() const { return this->transform.data(); }
    inline operator const Matrix4f&() const { return this->transform; }

    inline static Transform IDENTITY() { return Transform(); }

private:
    Vector3i Pixel2Hex(const Vector3f& pixel) const
    {
        // FIXME: rework this pls
        const auto& inversedHexBasis = HEX_BASIS.getInversed();

        const auto mulResult = inversedHexBasis * Vector2f{ pixel.x(), pixel.y() };

        //        auto     first   = (inversedHexBasis.getRow(0).x() * pixel.x() * GAME_WINDOW_WIDTH +
        //                      inversedHexBasis.getRow(0).y() * pixel.y() * GAME_WINDOW_HEIGHT);
        //        auto     second  = (inversedHexBasis.getRow(1).x() * pixel.x() * GAME_WINDOW_WIDTH +
        //                       inversedHexBasis.getRow(1).y() * pixel.y() * GAME_WINDOW_HEIGHT);
        //        Vector3i loooool = { first, second, -first - second };
        return Vector3i{ (int)mulResult.x(), (int)mulResult.y(), (int)(-mulResult.x() - mulResult.y()) };
    }

    Vector3f Hex2Pixel(const Vector3i& hex)
    {
        const auto& pixel = hex.x() * HEX_BASIS.getCol(0) + hex.y() * HEX_BASIS.getCol(1);
        return { pixel.x() /*/ GAME_WINDOW_WIDTH*/, pixel.y() /*/ GAME_WINDOW_HEIGHT*/, 0 };
    }

}; // class Transform
