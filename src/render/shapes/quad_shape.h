#pragma once

#include "ishape.h"

#include "game/game_configuration.h"

#include <vector>

class QuadShape : public IShape
{
public:
    static constexpr Type SHAPE_TYPE{ Type::QUAD };

public:
    QuadShape(const std::size_t   size          = 0,
              const RenderingMode renderingMode = GL_TRIANGLES)
        : IShape(renderingMode)
    {
    }
    virtual ~QuadShape() {}

    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(this->SHAPE_TYPE);
    }

    virtual bool Initialize() override
    {

        const float scaleFactor = 1.5;
        // x,	 y,	   z
        vertexPositionData.push_back((float)SHORT_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back((float)LONG_DIAGONAL / GAME_WINDOW_HEIGHT /
                                     scaleFactor);
        vertexPositionData.push_back(-0.3f); // v0
        vertexPositionData.push_back((float)SHORT_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back(-(float)LONG_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back(-0.3f); // v1
        vertexPositionData.push_back(-(float)SHORT_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back(-(float)LONG_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back(-0.3f); // v2
        vertexPositionData.push_back(-(float)SHORT_DIAGONAL /
                                     GAME_WINDOW_HEIGHT / scaleFactor);
        vertexPositionData.push_back((float)LONG_DIAGONAL / GAME_WINDOW_HEIGHT /
                                     scaleFactor);
        vertexPositionData.push_back(-0.3f); // v3

        return true;
    }

    virtual void Release() const override {}

    virtual const std::size_t GetVertexesCount() const override
    {
        return this->VERTEX_COUNT;
    }

    virtual const std::size_t GetTrianglesCount() const override
    {
        return this->TRIANGLE_COUNT;
    }

    virtual const std::size_t GetIndexesCount() const override
    {
        return this->INDEX_COUNT;
    }

    virtual const std::size_t GetLinesCount() const override
    {
        return this->LINES_COUNT;
    }

    virtual const VertexPositionData* GetPositions() const override
    {
        return this->vertexPositionData.data();
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
        return this->VERTEX_TEX_COORD_DATA;
    }

    virtual const VertexColorData* GetColors() const override
    {
        return nullptr;
    }

private:
    static constexpr std::size_t VERTEX_COUNT{ 4 };

    static constexpr std::size_t TRIANGLE_COUNT{ 2 };

    static constexpr std::size_t INDEX_COUNT{ 6 };

    static constexpr std::size_t LINES_COUNT{ 6 };

    std::vector<VertexPositionData> vertexPositionData;

    static constexpr VertexNormalData
        VERTEX_NORM_DATA[VERTEX_COUNT * VERTEX_NORMAL_DATA_ELEMENT_LEN]{
            // x,   y,	 z
            0.0f, 1.0f, 0.0f, // n0
            0.0f, 1.0f, 0.0f, // n1
            0.0f, 1.0f, 0.0f, // n2
            0.0f, 1.0f, 0.0f  // n3
        };

    static constexpr VertexTexCoordData
        VERTEX_TEX_COORD_DATA[VERTEX_COUNT * VERTEX_TEXCOORD_DATA_ELEMENT_LEN]{
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };

    static constexpr VertexIndexData VERTEX_IDX_DATA[INDEX_COUNT]{
        0, 1, 3, // t1
        1, 2, 3  // t2
    };
};
