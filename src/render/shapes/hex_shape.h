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
             const RenderingMode renderingMode = GL_TRIANGLES)
        : IShape(renderingMode)
        , hexesCount(size)
        , hexMapSize(size, size)
    {
        const auto& diagonal = hexMapSize.x() * 2 - 1;
        gridMapSize.x()      = diagonal * 3 + 1;
        gridMapSize.y()      = diagonal * 2;
    };
    virtual ~HexShape() = default;

public:
    virtual inline ShapeID GetShapeID() const override
    {
        std::size_t seed = hexMapSize.x();

        seed ^= (std::size_t)(static_cast<ShapeID>(SHAPE_TYPE) + 0x9e3779b9 +
                              (seed << 6) + (seed >> 2));

        seed ^= (std::size_t)(this->hexMapSize.x() + 0x9e3779b9 + (seed << 6) +
                              (seed >> 2));

        seed ^= (std::size_t)(this->GetRenderingMode() + 0x9e3779b9 +
                              (seed << 6) + (seed >> 2));

        return seed;
    }

    virtual bool Initialize() override
    {

        vertexPositionData.clear();
        vertexNormalData.clear();
        vertexIndexData.clear();

        // для каждого гекса из мапы:
        // 1) получить все его вершины;
        // 2) добавить их в set при этом создавая
        //    набор индексов для треугольников/линий
        std::vector<Vector3f> tmp;
        std::vector<Vector3f> hexVertexes;
        for (int i = -hexMapSize.x() + 1; i < hexMapSize.x(); ++i)
        {
            for (int j = -hexMapSize.x() - (i > 0 ? -1 : i - 1);
                 j < (i > 0 ? hexMapSize.x() - i : hexMapSize.x());
                 ++j)
            {
                hexVertexes = this->GetVertHexVertices(Vector3f{ i, j, 0.0f });
                for (auto& vert : hexVertexes)
                {
                    vert = Vector3f{ vert.x() / GAME_WINDOW_WIDTH,
                                     vert.y() / GAME_WINDOW_HEIGHT,
                                     0.0f };
                }
                this->vectorOfVertexes.push_back(hexVertexes);
                this->vertexesSet.insert(hexVertexes.begin(),
                                         hexVertexes.end());
            }
        }

        std::vector<Vector3f> vector;
        vector.reserve(vertexesSet.size());
        for (auto it = vertexesSet.begin(); it != vertexesSet.end();)
        {
            vector.push_back(std::move(vertexesSet.extract(it++).value()));
            this->vertexPositionData.push_back(vector.back().x());
            this->vertexPositionData.push_back(vector.back().y());
            this->vertexPositionData.push_back(
                this->GetRenderingMode() == GL_LINES ? -0.1 : 0.0);
        }

        // для каждого гекса взять вершины и создать индексы
        for (const auto& vertexes : vectorOfVertexes)
        {

            const auto& indexes = GetVertexesIndexes(vertexes, vector);

            this->GetRenderingMode() == GL_TRIANGLES
                ? GetTrianglesIndexes(indexes)
                : GetLinesIndexes(indexes);
        }

        this->indexesCount  = vertexIndexData.size();
        this->vertexesCount = vertexPositionData.size() / 3;

        return true;
    }

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
        return nullptr; /*vertexNormalData.data();*/
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
        const std::vector<Vector3f>& vector)
    {
        std::vector<std::size_t> vertexesIndexes;
        vertexesIndexes.reserve(vertexes.size());
        for (const auto& v : vertexes)
        {
            auto        vertex = std::find_if(vector.begin(),
                                       vector.end(),
                                       [&](const Vector3f& vertex)
                                       { return vertex == v; });
            std::size_t index  = std::distance(vector.begin(), vertex);
            if (index == vector.size())
            {
                // invalid
                continue;
            }
            vertexesIndexes.emplace_back(std::move(index));
        }
        return vertexesIndexes;
    }

    void GetLinesIndexes(const std::vector<std::size_t>& indexes)
    {
        if (indexes.size() < 7)
        {
            return;
        }

        for (int i = 0; i < COUNT_OF_LINES_IN_HEX - 1; ++i)
        {
            vertexIndexData.push_back(indexes[i + 1]);
            vertexIndexData.push_back(indexes[i + 2]);
        }

        vertexIndexData.push_back(indexes[COUNT_OF_LINES_IN_HEX]);
        vertexIndexData.push_back(indexes[1]);
    }

    void GetTrianglesIndexes(const std::vector<std::size_t>& indexes)
    {
        if (indexes.size() < 7)
        {
            return;
        }

        for (int i = 0; i < COUNT_OF_TRIANGLES_IN_HEX - 1; ++i)
        {

            vertexIndexData.push_back(indexes[0]);
            vertexIndexData.push_back(indexes[i + 1]);
            vertexIndexData.push_back(indexes[i + 2]);
        }

        vertexIndexData.push_back(indexes[0]);
        vertexIndexData.push_back(indexes[COUNT_OF_TRIANGLES_IN_HEX]);
        vertexIndexData.push_back(indexes[1]);
    }

    Vector3f Hex2Pixel(const Vector3f& hex)
    {
        const auto& pixel =
            hex.x() * HEX_BASIS.getCol(0) + hex.y() * HEX_BASIS.getCol(1);
        return { pixel.x(), pixel.y(), -pixel.x() - pixel.y() };
    }

    std::vector<Vector3f> GetVertHexVertices(const Vector3f& hex)
    {
        const auto& pixel = Hex2Pixel(hex);
        return {
            pixel,
            pixel + 2 * Vector3f{ GRID_BASIS.getCol(0).x(),
                                  GRID_BASIS.getCol(0).y(),
                                  0.0 },
            pixel +
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel -
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel - 2 * Vector3f{ GRID_BASIS.getCol(0).x(),
                                  GRID_BASIS.getCol(0).y(),
                                  0.0 },
            pixel -
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel +
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 }
        };
    }

    std::vector<Vector3f> GetHorHexVertices(const Vector3f& hex)
    {
        const auto& pixel = Hex2Pixel(hex);
        return {
            pixel,
            pixel +
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel +
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel + 2 * Vector3f{ GRID_BASIS.getCol(1).x(),
                                  GRID_BASIS.getCol(1).y(),
                                  0.0 },
            pixel -
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel -
                Vector3f{
                    GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                Vector3f{
                    GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
            pixel - 2 * Vector3f{ GRID_BASIS.getCol(1).x(),
                                  GRID_BASIS.getCol(1).y(),
                                  0.0 },
        };
    }

private:
    std::size_t hexesCount;

    std::size_t vertexesCount{ 7 };
    std::size_t trianglesCount{ 6 };
    std::size_t linesCount{ 6 };
    std::size_t indexesCount{ 18 };

    std::vector<VertexPositionData> vertexPositionData{
        // x     y       z
        0.0f,  0.0f,    0.0f, // v0
        0.0f,  0.866f,  0.0,  // v1
        0.5f,  0.433f,  0.0f, // v2
        0.5f,  -0.433f, 0.0f, // v3
        0.0f,  -0.866f, 0.0f, // v4
        -0.5f, -0.433f, 0.0f, // v5
        -0.5f, 0.433f,  0.0,  // v6
        0.0f,  0.866f,  0.0f  // v7

    };
    std::vector<VertexNormalData> vertexNormalData{
        // x    y     z
        0.0f, 1.0f, 0.0f, // n0
        0.0f, 1.0f, 0.0f, // n1
        0.0f, 1.0f, 0.0f, // n2
        0.0f, 1.0f, 0.0f, // n3
        0.0f, 1.0f, 0.0f, // n4
        0.0f, 1.0f, 0.0f, // n5
        0.0f, 1.0f, 0.0f, // n6
        0.0f, 1.0f, 0.0f  // n7
    };
    std::vector<VertexIndexData> vertexIndexData{
        0, 1, 2, // tr0
        0, 2, 3, // tr1
        0, 3, 4, // tr2
        0, 4, 5, // tr3
        0, 5, 6, // tr4
        0, 6, 1  // tr5
    };

    std::unordered_set<Vector3f>       vertexesSet;
    std::vector<std::vector<Vector3f>> vectorOfVertexes;
};
