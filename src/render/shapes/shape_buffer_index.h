#pragma once

#include <utility>

class ShapeBufferIndex
{
    friend class RenderSystem;
    friend class Renderer;

protected:
    ShapeID shapeId;

    std::size_t positionDataIndex;

    std::size_t indexDataIndex;

    std::size_t normalDataIndex;

    std::size_t texCoordDataIndex;

    std::size_t colorDataIndex;

public:
    ShapeBufferIndex()
        : positionDataIndex(-1)
        , indexDataIndex(-1)
        , normalDataIndex(-1)
        , texCoordDataIndex(-1)
        , colorDataIndex(-1)
        , shapeId(INVALID_SHAPE_ID)
    {
    }

    inline std::size_t GetPositionDataIndex() const { return this->positionDataIndex; }

    inline std::size_t GetIndexDataIndex() const { return this->indexDataIndex; }

    inline std::size_t GetNormalDataIndex() const { return this->normalDataIndex; }

    inline std::size_t GetTexCoordDataIndex() const { return this->texCoordDataIndex; }

    inline std::size_t GetColorDataIndex() const { return this->colorDataIndex; }

    inline ShapeID GetShapeId() const { return this->shapeId; }

}; // class ShapeBufferIndex
