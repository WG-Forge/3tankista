#pragma once

#include "ishape.h"

#include <vector>

class MapShape : public IShape
{
public:
    MapShape()
        : VERTEX_POS_DATA()
        , VERTEX_NORM_DATA()
        , VERTEX_IDX_DATA()
    {
    }
    virtual ~MapShape() {}

    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(this->SHAPE_TYPE);
    }

    virtual bool Initialize() const override
    {
        // TODO: move code from hexagonale_field project
    }

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
        return this->VERTEX_POS_DATA.data();
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
    std::size_t VERTEX_COUNT{ 0 };
    std::size_t TRIANGLE_COUNT{ 0 };
    std::size_t INDEX_COUNT{ 0 };

    std::vector<VertexPositionData> VERTEX_POS_DATA;
    std::vector<VertexNormalData>   VERTEX_NORM_DATA;
    std::vector<VertexIndexData>    VERTEX_IDX_DATA;

    Type SHAPE_TYPE{ Type::MAP };
};
