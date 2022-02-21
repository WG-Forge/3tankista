#pragma once

#include "game/game_configuration.h"

#include "ishape.h"

#include "utility/matrix.hpp"

#include <cmath>
#include <unordered_set>
#include <vector>

class HexShape : public IShape
{

    inline static constexpr std::size_t COUNT_OF_TRIANGLES_IN_HEX{ 6 };
    inline static constexpr std::size_t COUNT_OF_LINES_IN_HEX{ 6 };

    Vector2f hexMapSize;
    Vector2f gridMapSize;

public:
    static constexpr Type SHAPE_TYPE{ Type::HEX };

public:
    HexShape(const std::size_t   size          = 1,
             const RenderingMode renderingMode = GL_TRIANGLES);
    ;
    virtual ~HexShape() = default;

public:
    virtual ShapeID GetShapeID() const override;

    virtual bool Initialize() override;

    virtual void Release() const override {}

    virtual const std::size_t GetVertexesCount() const override
    {
        return vertexesCount;
    }

    virtual const std::size_t GetTrianglesCount() const override
    {
        return trianglesCount;
    }

    virtual const std::size_t GetLinesCount() const override
    {
        return linesCount;
    }

    virtual const std::size_t GetIndexesCount() const override
    {
        return indexesCount;
    }

    virtual const VertexPositionData* GetPositions() const override
    {
        return vertexPositionData.data();
    }

    virtual const VertexIndexData* GetIndexes() const override
    {
        return vertexIndexData.data();
    }

    virtual const VertexNormalData* GetNormals() const override
    {
        return nullptr;
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
    std::vector<std::size_t> GetVertexesIndexes(
        const std::vector<Vector3f>& vertexes,
        const std::vector<Vector3f>& vector);

    void GetLinesIndexes(const std::vector<std::size_t>& indexes);

    void GetTrianglesIndexes(const std::vector<std::size_t>& indexes);

    Vector3f Hex2Pixel(const Vector3i& hex);

    std::vector<Vector3f> GetVertHexVertices(const Vector3i& hex);

    std::vector<Vector3f> GetHorHexVertices(const Vector3i& hex);

private:
    std::size_t hexesCount{ 0 };

    std::size_t vertexesCount{ 0 };
    std::size_t trianglesCount{ 0 };
    std::size_t linesCount{ 0 };
    std::size_t indexesCount{ 0 };

    std::vector<VertexPositionData> vertexPositionData{};
    std::vector<VertexNormalData>   vertexNormalData{};
    std::vector<VertexIndexData>    vertexIndexData{};

    std::unordered_set<Vector3f>       vertexesSet;
    std::vector<std::vector<Vector3f>> vectorOfVertexes;
};
