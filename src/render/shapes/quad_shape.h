#pragma once

#include "ishape.h"

#include "game/game_configuration.h"

#include <vector>

class QuadShape : public IShape
{
public:
    static constexpr Type SHAPE_TYPE{ Type::QUAD };

public:
    QuadShape(const std::size_t size = 0, const RenderingMode renderingMode = GL_TRIANGLES);
    virtual ~QuadShape() = default;

    virtual inline ShapeID GetShapeID() const override { return static_cast<ShapeID>(this->SHAPE_TYPE); }

    virtual bool Initialize() override;

    virtual void Release() const override {}

    virtual const std::size_t GetVertexesCount() const override { return this->VERTEX_COUNT; }

    virtual const std::size_t GetTrianglesCount() const override { return this->TRIANGLE_COUNT; }

    virtual const std::size_t GetIndexesCount() const override { return this->INDEX_COUNT; }

    virtual const std::size_t GetLinesCount() const override { return this->LINES_COUNT; }

    virtual const VertexPositionData* GetPositions() const override { return this->vertexPositionData.data(); }

    virtual const VertexIndexData* GetIndexes() const override { return this->vertexIdxData.data(); }

    virtual const VertexNormalData* GetNormals() const override { return nullptr; }

    virtual const VertexTexCoordData* GetTexCoords() const override { return this->vertexTexCoordData.data(); }

    virtual const VertexColorData* GetColors() const override { return nullptr; }

private:
    static constexpr std::size_t VERTEX_COUNT{ 4 };

    static constexpr std::size_t TRIANGLE_COUNT{ 2 };

    static constexpr std::size_t LINES_COUNT{ 3 };

    static constexpr std::size_t INDEX_COUNT{ 6 };

    inline static constexpr float zCoord = -0.3f;

    inline static constexpr float scaleFactor = 1.5;

    inline static const std::vector<VertexPositionData> vertexPositionData{
        (float)SHORT_DIAGONAL / scaleFactor,
        (float)LONG_DIAGONAL / scaleFactor,
        zCoord, // v0
        (float)SHORT_DIAGONAL / scaleFactor,
        -(float)LONG_DIAGONAL / scaleFactor,
        zCoord, // v1
        -(float)SHORT_DIAGONAL / scaleFactor,
        -(float)LONG_DIAGONAL / scaleFactor,
        zCoord, // v2
        -(float)SHORT_DIAGONAL / scaleFactor,
        (float)LONG_DIAGONAL / scaleFactor,
        zCoord // v3
    };

    inline static const std::vector<VertexTexCoordData> vertexTexCoordData{ 1.0f, 1.0f, 1.0f, 0.0f,
                                                                            0.0f, 0.0f, 0.0f, 1.0f };

    inline static const std::vector<VertexIndexData> vertexIdxData{
        0, 1, 3, // t1
        1, 2, 3  // t2
    };
};
