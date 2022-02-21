#pragma once

#include "render/shapes/ishape.h"

#include "utility/matrix.hpp"

#include "game/game_configuration.h"

#include <cmath>

class RoundShape : public IShape
{
public:
    static constexpr Type SHAPE_TYPE{ Type::CIRCLE };

public:
    RoundShape(const std::size_t   size          = 0,
               const RenderingMode renderingMode = GL_TRIANGLES);

    virtual ~RoundShape() = default;

    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(this->SHAPE_TYPE);
    }

    virtual bool Initialize() override;

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
    std::size_t vertexCount{ 0 };

    std::size_t triangleCount{ 0 };

    std::size_t linesCount{ 0 };

    std::size_t indexCount{ 0 };

    std::vector<VertexPositionData> vertexPositionData{};

    std::vector<VertexNormalData> vertexNormalData{};

    std::vector<VertexIndexData> vertexIndexData{};
};
