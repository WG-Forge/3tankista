#pragma once

#include "ishape.h"

#include "utility/matrix.hpp"

#include "game/game_configuration.h"

#include <cmath>

class RoundShape : public IShape
{
public:
    static constexpr Type SHAPE_TYPE{ Type::CIRCLE };

public:
    RoundShape(const std::size_t   size          = 0,
               const RenderingMode renderingMode = GL_TRIANGLES)
        : IShape(renderingMode)
    {
    }

    virtual ~RoundShape() = default;

    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(this->SHAPE_TYPE);
    }

    virtual bool Initialize() override
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
            vertexPositionData.push_back(-0.2f);

            vertexPositionData.push_back(v2.x() / GAME_WINDOW_WIDTH);
            vertexPositionData.push_back(v2.y() / GAME_WINDOW_HEIGHT);
            vertexPositionData.push_back(-0.2f);

            r1 = r2;
            v1 = v2;
        }

        for (std::size_t i = 1; i < vertexPositionData.size() / 3.0 - 1; ++i)
        {
            vertexIndexData.push_back(0);
            vertexIndexData.push_back(i);
            vertexIndexData.push_back(i + 1);
        }

        this->vertexCount = vertexPositionData.size() / 3;
        this->indexCount  = vertexIndexData.size();

        return true;
    }

    virtual void Release() const override {}

    virtual const std::size_t GetVertexesCount() const override
    {
        return this->vertexCount;
    }

    virtual const std::size_t GetTrianglesCount() const override
    {
        return this->triangleCount;
    }

    virtual const std::size_t GetLinesCount() const override
    {
        return this->linesCount;
    }

    virtual const std::size_t GetIndexesCount() const override
    {
        return this->indexCount;
    }

    virtual const VertexPositionData* GetPositions() const override
    {
        return this->vertexPositionData.data();
    }

    virtual const VertexIndexData* GetIndexes() const override
    {
        return this->vertexIndexData.data();
    }

    virtual const VertexNormalData* GetNormals() const override
    {
        return this->vertexNormalData.data();
    }

    virtual const VertexTexCoordData* GetTexCoords() const override
    {
        return nullptr;
    }

    virtual const VertexColorData* GetColors() const override
    {
        return nullptr;
    }

private:
    std::size_t vertexCount{ 4 };

    std::size_t triangleCount{ 2 };

    std::size_t linesCount{ 6 };

    std::size_t indexCount{ 6 };

    std::vector<VertexPositionData> vertexPositionData{
        // x,	 y,	   z
        -1.0f, -1.0f, 0.0f, // v0
        -1.0f, 1.0f,  0.0f, // v1
        1.0f,  1.0f,  0.0f, // v2
        1.0f,  -1.0f, 0.0f  // v3
    };

    std::vector<VertexNormalData> vertexNormalData{
        // x,   y,	 z
        0.0f, 1.0f, 0.0f, // n0
        0.0f, 1.0f, 0.0f, // n1
        0.0f, 1.0f, 0.0f, // n2
        0.0f, 1.0f, 0.0f  // n3
    };

    std::vector<VertexIndexData> vertexIndexData{
        0, 1, 2, // t1
        0, 2, 3  // t2
    };
};
