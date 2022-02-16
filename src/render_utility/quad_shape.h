#pragma once

#include "ishape.h"

class QuadShape : public IShape
{
public:
    QuadShape() {}
    virtual ~QuadShape() {}

    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(this->SHAPE_TYPE);
    }

    virtual bool Initialize() const override { return true; }

    virtual void Release() const override {}

    virtual const std::size_t GetVertexCount() const override
    {
        return this->VERTEX_COUNT;
    }

    virtual const std::size_t GetTriangleCount() const override
    {
        return this->TRIANGLE_COUNT;
    }

    virtual const std::size_t GetIndexCount() const override
    {
        return this->INDEX_COUNT;
    }

    virtual const VertexPositionData* GetPositions() const override
    {
        return this->VERTEX_POS_DATA;
    }

    virtual const VertexIndexData* GetIndexes() const override
    {
        return this->VERTEX_IDX_DATA;
    }

    virtual const VertexNormalData* GetNormals() const override
    {
        return this->VERTEX_NORM_DATA;
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
    static constexpr std::size_t VERTEX_COUNT{ 4 };

    static constexpr std::size_t TRIANGLE_COUNT{ 2 };

    static constexpr std::size_t INDEX_COUNT{ 6 };

    static constexpr VertexPositionData
        VERTEX_POS_DATA[VERTEX_COUNT * VERTEX_POSITION_DATA_ELEMENT_LEN]{
            // x,	 y,	   z
            -1.0f, -1.0f, 0.0f, // v0
            -1.0f, 1.0f,  0.0f, // v1
            1.0f,  1.0f,  0.0f, // v2
            1.0f,  -1.0f, 0.0f  // v3
        };

    static constexpr VertexNormalData
        VERTEX_NORM_DATA[VERTEX_COUNT * VERTEX_NORMAL_DATA_ELEMENT_LEN]{
            // x,   y,	 z
            0.0f, 1.0f, 0.0f, // n0
            0.0f, 1.0f, 0.0f, // n1
            0.0f, 1.0f, 0.0f, // n2
            0.0f, 1.0f, 0.0f  // n3
        };

    static constexpr VertexIndexData VERTEX_IDX_DATA[INDEX_COUNT]{
        0, 1, 2, // t1
        0, 2, 3  // t2
    };

    static constexpr Type SHAPE_TYPE{ Type::QUAD };
};
