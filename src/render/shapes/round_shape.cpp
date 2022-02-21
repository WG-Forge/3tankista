#include "round_shape.h"

RoundShape::RoundShape(const std::size_t   size,
                       const RenderingMode renderingMode)
    : IShape(renderingMode)
{
}

bool RoundShape::Initialize()
{

    this->vertexPositionData.clear();
    this->vertexIndexData.clear();
    this->vertexNormalData.clear();

    const float NUM_SEGMENTS = 16.0f;

    const float STEP = 2 * M_PI / NUM_SEGMENTS;

    float c = std::cos(STEP);
    float s = std::sin(STEP);

    Vector2f r1(1.0f, 0.0f);
    Vector2f v1 = LONG_DIAGONAL * r1;

    static constexpr float zCoord = -0.2f;

    vertexPositionData.push_back(0.0f);
    vertexPositionData.push_back(0.0f);
    vertexPositionData.push_back(-0.2f);

    for (size_t i = 0; i < NUM_SEGMENTS; ++i)
    {
        Vector2f r2;

        r2.x()      = c * r1.x() - s * r1.y();
        r2.y()      = s * r1.x() + c * r1.y();
        Vector2f v2 = LONG_DIAGONAL * r2;

        vertexPositionData.push_back(v1.x() / GAME_WINDOW_WIDTH);
        vertexPositionData.push_back(v1.y() / GAME_WINDOW_HEIGHT);
        vertexPositionData.push_back(zCoord);

        vertexPositionData.push_back(v2.x() / GAME_WINDOW_WIDTH);
        vertexPositionData.push_back(v2.y() / GAME_WINDOW_HEIGHT);
        vertexPositionData.push_back(zCoord);

        r1 = r2;
        v1 = v2;
    }

    for (std::size_t i = 1; i < vertexPositionData.size() / 3.0 - 1; ++i)
    {
        vertexIndexData.push_back(0);
        vertexIndexData.push_back(i);
        vertexIndexData.push_back(i + 1);
    }

    this->vertexCount   = vertexPositionData.size() / 3;
    this->triangleCount = vertexIndexData.size() / 3;
    this->linesCount    = vertexIndexData.size() / 2;
    this->indexCount    = vertexIndexData.size();

    return true;
}
