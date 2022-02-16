#pragma once

#include "opengl.h"

#include <cstdint>

using ShapeID = uint16_t;

static constexpr ShapeID INVALID_SHAPE_ID{ 0xffff };

class IShape
{
public:
    enum class Type : uint16_t
    {
        INVALID_SHAPE = INVALID_SHAPE_ID,
        TRIANGLE      = 0,
        QUAD          = 1,
        HEX           = 2,
        MAX_SHAPES
    };

public:
    IShape()          = default;
    virtual ~IShape() = default;

    virtual inline ShapeID GetShapeID() const
    {
        return static_cast<ShapeID>(Type::INVALID_SHAPE);
    }

    virtual bool Initialize() = 0;

    virtual void Release() const = 0;

    virtual const std::size_t GetVertexesCount() const = 0;

    virtual const std::size_t GetTrianglesCount() const = 0;

    virtual const std::size_t GetLinesCount() const = 0;

    virtual const std::size_t GetIndexesCount() const = 0;

    virtual const VertexPositionData* GetPositions() const = 0;

    virtual const VertexIndexData* GetIndexes() const = 0;

    virtual const VertexNormalData* GetNormals() const = 0;

    virtual const VertexTexCoordData* GetTexCoords() const = 0;

    virtual const VertexColorData* GetColors() const = 0;
};
