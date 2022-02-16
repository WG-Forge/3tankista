#pragma once

#include "game/game_configuration.h"

#include "ishape.h"

#include "utility/matrix.hpp"

#include <cmath>
#include <unordered_set>
#include <vector>

class HexShape : public IShape
{
    inline static constexpr std::size_t hexSize = 32 * 1.75;
    inline static constexpr std::size_t longDiagonal =
        hexSize * std::sqrt(3) / 2.0; // 1/2 from short hex diagonal
    inline static const std::size_t shortDiagonal =
        hexSize / 2.0; // 1/4 from long hex diagonal

    Matrix2f hexBasis;
    Matrix2f gridBasis;

    Vector2f hexMapSize;
    Vector2f gridMapSize;

public:
    static constexpr Type SHAPE_TYPE{ Type::HEX };

public:
    HexShape(const std::size_t size = 1)
        : hexesCount(size)
        , hexMapSize(size, size)
    {
        // init gridBasis
        gridBasis.replaceCol(0, Vector2f(shortDiagonal, 0));
        gridBasis.replaceCol(1, Vector2f(0, longDiagonal));

        // init hexBasis
        hexBasis.replaceCol(0, gridBasis.getCol(0) * 3 + gridBasis.getCol(1));
        hexBasis.replaceCol(1, gridBasis.getCol(1) * 2);

        const auto& diagonal = hexMapSize.x() * 2 - 1;
        gridMapSize.x()      = diagonal * 3 + 1;
        gridMapSize.y()      = diagonal * 2;
    };
    virtual ~HexShape() = default;

public:
    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(SHAPE_TYPE);
    }

    virtual bool Initialize() override
    {
        // для каждого гекса из мапы:
        // 1) получить все его вершины;
        // 2) добавить их в set при этом создавая
        //    набор индексов для треугольников/линий

        vertexPositionData.clear();
        vertexNormalData.clear();
        vertexIndexData.clear();

        std::vector<Vector3f> tmp;
        std::vector<Vector2f> hexVertexes;
        for (int i = -hexMapSize.x() + 1; i < hexMapSize.x(); ++i)
        {
            for (int j = -hexMapSize.x() - (i > 0 ? -1 : i - 1);
                 j < (i > 0 ? hexMapSize.x() - i : hexMapSize.x());
                 ++j)
            {
                std::cout << "[ " << i << " , " << j << " ]" << std::endl;
                hexVertexes = this->getVertHexVertices(Vector2f{ i, j });
                for (auto& vert : hexVertexes)
                {
                    vert = Vector2f{ vert.x() / GAME_WINDOW_WIDTH,
                                     vert.y() / GAME_WINDOW_HEIGHT };
                }
                vectorOfVertexes.push_back(hexVertexes);
                vertexesSet.insert(hexVertexes.begin(), hexVertexes.end());
            }
        }

        std::vector<Vector2f> vector;
        vector.reserve(vertexesSet.size());
        for (auto it = vertexesSet.begin(); it != vertexesSet.end();)
        {
            vector.push_back(std::move(vertexesSet.extract(it++).value()));
            vertexPositionData.push_back(vector.back().x());
            vertexPositionData.push_back(vector.back().y());
            vertexPositionData.push_back(0);
        }

        // для каждого гекса взять вершины и создать индексы
        for (const auto& vertexes : vectorOfVertexes)
        {
            auto        zeroVertex = std::find_if(vector.begin(),
                                           vector.end(),
                                           [&](const Vector2f& vertex)
                                           { return vertex == vertexes[0]; });
            std::size_t zeroIndex  = std::distance(vector.begin(), zeroVertex);
            if (zeroIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        firstVertex = std::find_if(vector.begin(),
                                            vector.end(),
                                            [&](const Vector2f& vertex)
                                            { return vertex == vertexes[1]; });
            std::size_t firstIndex = std::distance(vector.begin(), firstVertex);
            if (firstIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        secondVertex = std::find_if(vector.begin(),
                                             vector.end(),
                                             [&](const Vector2f& vertex)
                                             { return vertex == vertexes[2]; });
            std::size_t secondIndex =
                std::distance(vector.begin(), secondVertex);
            if (secondIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        thirdVertex = std::find_if(vector.begin(),
                                            vector.end(),
                                            [&](const Vector2f& vertex)
                                            { return vertex == vertexes[3]; });
            std::size_t thirdIndex = std::distance(vector.begin(), thirdVertex);
            if (thirdIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        fourthVertex = std::find_if(vector.begin(),
                                             vector.end(),
                                             [&](const Vector2f& vertex)
                                             { return vertex == vertexes[4]; });
            std::size_t fourthIndex =
                std::distance(vector.begin(), fourthVertex);
            if (fourthIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        fivthVertex = std::find_if(vector.begin(),
                                            vector.end(),
                                            [&](const Vector2f& vertex)
                                            { return vertex == vertexes[5]; });
            std::size_t fivthIndex = std::distance(vector.begin(), fivthVertex);
            if (fivthIndex == vector.size())
            {
                // invalid
                return false;
            }
            auto        sixthVertex = std::find_if(vector.begin(),
                                            vector.end(),
                                            [&](const Vector2f& vertex)
                                            { return vertex == vertexes[6]; });
            std::size_t sixthIndex = std::distance(vector.begin(), sixthVertex);
            if (sixthIndex == vector.size())
            {
                // invalid
                return false;
            }

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(firstIndex);
            vertexIndexData.push_back(secondIndex);

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(secondIndex);
            vertexIndexData.push_back(thirdIndex);

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(thirdIndex);
            vertexIndexData.push_back(fourthIndex);

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(fourthIndex);
            vertexIndexData.push_back(fivthIndex);

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(fivthIndex);
            vertexIndexData.push_back(sixthIndex);

            vertexIndexData.push_back(zeroIndex);
            vertexIndexData.push_back(sixthIndex);
            vertexIndexData.push_back(firstIndex);
        }

        /*
        vertexPositionData.clear();
        vertexNormalData.clear();
        vertexIndexData.clear();

                // initialize with size;
                const auto  parity   = this->hexesCount % 2;
                const auto& diagonal = this->hexesCount * 2 - 1;
                const auto  offset =
                    Vector2f(diagonal * longDiagonal,
                             (2 + 3 * (this->hexesCount - 1)) * shortDiagonal);

                Vector2f gridMapSize;
                gridMapSize.x() = diagonal * 2;
                gridMapSize.y() = diagonal * 3 + 1;

                //

                        int start = 0;
                        for (int i = 0; i < gridMapSize.y() / 2; i += 3)
                        {
                            start = this->hexesCount - i / 3 - 1;
                            for (int j = start; j < gridMapSize.x() / 2; ++j)
                            {
                                if (std::abs(i % 2 - j % 2) != parity)
                                {
                                    const auto& firstPoint = gridBasis.getCol(0)
           * j + gridBasis.getCol(1) * (i + 1) - offset;
           vertexPositionData.push_back(firstPoint.x() / GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(firstPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0);

                                    const auto& secondPoint =
           gridBasis.getCol(0) * (j + 1) + gridBasis.getCol(1) * i - offset;
                                    vertexPositionData.push_back(secondPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(secondPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);

                                    const auto& thirdPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j) + gridBasis.getCol(1) * (i + 1) - offset;
                                    vertexPositionData.push_back(thirdPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(thirdPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);
                                    const auto& fourthPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j - 1)
                   + gridBasis.getCol(1) * i - offset;
                                    vertexPositionData.push_back(fourthPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(fourthPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);

                                    const auto& fivethPoint =
                                        gridBasis.getCol(0) * (j) +
                                        gridBasis.getCol(1) * (gridMapSize.y() -
           i - 1)
                   - offset; vertexPositionData.push_back(fivethPoint.x() /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(fivethPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           sixthPoint = gridBasis.getCol(0) * (j + 1) + gridBasis.getCol(1) *
           (gridMapSize.y() - i) - offset;
           vertexPositionData.push_back(sixthPoint.x() / GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(sixthPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0);

                                    const auto& seventhPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j) + gridBasis.getCol(1) * (gridMapSize.y() - i - 1)
                   - offset; vertexPositionData.push_back(seventhPoint.x() /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(seventhPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           eightthPoint = gridBasis.getCol(0) * (gridMapSize.x() - j - 1)
                   + gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
                                    vertexPositionData.push_back(eightthPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(eightthPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);

                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           firstPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // firstPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           secondPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // secondPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           thirdPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // thirdPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           fourthPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // fourthPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           fivethPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // fivethPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           sixthPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // sixthPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           seventhPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // seventhPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           eightthPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // eightthPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                }
                                else
                                {
                                    const auto& firstPoint = gridBasis.getCol(0)
           * j + gridBasis.getCol(1) * i - offset;
           vertexPositionData.push_back(firstPoint.x() / GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(firstPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           secondPoint = gridBasis.getCol(0) * (j + 1) + gridBasis.getCol(1) *
           (i + 1) - offset; vertexPositionData.push_back(secondPoint.x() /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(secondPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0);

                                    const auto& thirdPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j) + gridBasis.getCol(1) * i - offset;
                                    vertexPositionData.push_back(thirdPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(thirdPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);
                                    const auto& fourthPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j - 1)
                   + gridBasis.getCol(1) * (i + 1) - offset;
                                    vertexPositionData.push_back(fourthPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(fourthPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);

                                    const auto& fivethPoint =
                                        gridBasis.getCol(0) * j +
                                        gridBasis.getCol(1) * (gridMapSize.y() -
           i) - offset; vertexPositionData.push_back(fivethPoint.x() /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(fivethPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           sixthPoint = gridBasis.getCol(0) * (j + 1) + gridBasis.getCol(1) *
           (gridMapSize.y() - i - 1)
                   - offset; vertexPositionData.push_back(sixthPoint.x() /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(sixthPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0);

                                    const auto& seventhPoint =
                                        gridBasis.getCol(0) * (gridMapSize.x() -
           j) + gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
           vertexPositionData.push_back(seventhPoint.x() / GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back(seventhPoint.y()
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           eightthPoint = gridBasis.getCol(0) * (gridMapSize.x() - j - 1)
                   + gridBasis.getCol(1) * (gridMapSize.y() - i - 1) - offset;
                                    vertexPositionData.push_back(eightthPoint.x()
           / GAME_WINDOW_WIDTH); vertexPositionData.push_back(eightthPoint.y() /
                                                                 GAME_WINDOW_HEIGHT);
                                    vertexPositionData.push_back(0.0);

                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           firstPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // firstPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           secondPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // secondPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           thirdPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // thirdPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           fourthPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // fourthPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           fivethPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // fivethPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           sixthPoint.x() /
                                    //                        GAME_WINDOW_WIDTH,
                                    // sixthPoint.y() /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           seventhPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // seventhPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                    //                    vertexesSet.insert(
                                    //                        Vector3f{
           eightthPoint.x()
                   /
                                    //                        GAME_WINDOW_WIDTH,
                                    // eightthPoint.y()
                   /
                                    // GAME_WINDOW_HEIGHT, 0.0f
                                    //                                  });
                                }
                            }
                        }

                        for (int i = 1; i < gridMapSize.y(); i += 3)
                        {
                            if (i <= gridMapSize.y() / 2)
                            {
                                start = this->hexesCount - 1 - i / 3;
                            }
                            else
                            {
                                start = (i - gridMapSize.y() / 2) / 3;
                            }

                            for (int j = parity - i % 2; j < gridMapSize.x() +
           1; j += 2)
                            {
                                if (j >= start && j <= gridMapSize.x() - start)
                                {
                                    const auto& firstPoint = gridBasis.getCol(0)
           * j + gridBasis.getCol(1) * i - offset;
           vertexPositionData.push_back((firstPoint.x()) / GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back((firstPoint.y())
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0); const auto&
           secondPoint = gridBasis.getCol(0) * j + gridBasis.getCol(1) * (i + 2)
           - offset; vertexPositionData.push_back((secondPoint.x()) /
                                                                 GAME_WINDOW_WIDTH);
                                    vertexPositionData.push_back((secondPoint.y())
           / GAME_WINDOW_HEIGHT); vertexPositionData.push_back(0.0);

                                    vertexesSet.insert(
                                        Vector2f{ firstPoint.x() /
           GAME_WINDOW_WIDTH, firstPoint.y() / GAME_WINDOW_HEIGHT
                   }); vertexesSet.insert(Vector2f{ secondPoint.x() /
           GAME_WINDOW_WIDTH, secondPoint.y() / GAME_WINDOW_HEIGHT,
                                    });
                                }
                            }
                        }

                        for (int i = 0; i < vertexPositionData.size() / 3; ++i)
                        {
                            this->vertexNormalData.push_back(0.0f);
                            this->vertexNormalData.push_back(1.0f);
                            this->vertexNormalData.push_back(0.0f);
                        }

                        for (int i = 0; i < vertexPositionData.size() / 3; ++i)
                        {
                            vertexIndexData.push_back(i);
                        }
                */
        indexesCount  = vertexIndexData.size();
        vertexesCount = vertexPositionData.size() / 3;

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
        return vertexNormalData.data();
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
    void insertVertex(const Vector2f& vertex)
    {
        //        const auto& result =
        //            vertexesSet.insert(Vector3f{ vertex.x(), vertex.y(), 0 });

        //        if (result.second == true)
        //        {
        // if vertex was inserted successfully
        //        }
        //        else
        //        {
        // if vertex was inserted before
        //        }
    }

    Vector2f hex2pixel(const Vector2f& hex)
    {
        const auto& pixel =
            hex.x() * hexBasis.getCol(0) + hex.y() * hexBasis.getCol(1);
        return pixel;
    }

    std::vector<Vector2f> getVertHexVertices(const Vector2f& hex)
    {
        const auto& pixel = hex2pixel(hex);
        return { pixel,
                 pixel + 2 * gridBasis.getCol(0),
                 pixel + gridBasis.getCol(0) + gridBasis.getCol(1),
                 pixel - gridBasis.getCol(0) + gridBasis.getCol(1),
                 pixel - 2 * gridBasis.getCol(0),
                 pixel - gridBasis.getCol(0) - gridBasis.getCol(1),
                 pixel + gridBasis.getCol(0) - gridBasis.getCol(1) };
    }

    std::vector<Vector2f> getHorHexVertices(const Vector2f& hex)
    {
        const auto& pixel = hex2pixel(hex);
        return {
            pixel,
            pixel + gridBasis.getCol(0) - gridBasis.getCol(1),
            pixel + gridBasis.getCol(0) + gridBasis.getCol(1),
            pixel + 2 * gridBasis.getCol(1),
            pixel - gridBasis.getCol(0) + gridBasis.getCol(1),
            pixel - gridBasis.getCol(0) - gridBasis.getCol(1),
            pixel - 2 * gridBasis.getCol(1),
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

    std::unordered_set<Vector2f>       vertexesSet;
    std::vector<std::vector<Vector2f>> vectorOfVertexes;
};
