#pragma once

#include "game/game_configuration.h"

#include "ishape.h"

#include "utility/matrix.hpp"

#include <cmath>
#include <vector>

class HexShape : public IShape
{
    inline static constexpr std::size_t hexSize = 50;
    inline static constexpr std::size_t longDiagonal =
        hexSize * std::sqrt(3) / 2.0;
    inline static const std::size_t shortDiagonal = hexSize / 2.0;

public:
    static constexpr Type SHAPE_TYPE{ Type::HEX };

public:
    HexShape(const std::size_t size = 1)
        : hexesCount(size){

        };
    virtual ~HexShape() = default;

public:
    virtual inline ShapeID GetShapeID() const override
    {
        return static_cast<ShapeID>(SHAPE_TYPE);
    }

    virtual bool Initialize() override
    {
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

        Matrix2f gridBasis = Matrix2f();
        Matrix2f hexBasis  = Matrix2f();

        gridBasis.replaceCol(0, Vector2f(longDiagonal, 0));
        gridBasis.replaceCol(1, Vector2f(0, shortDiagonal));

        hexBasis.replaceCol(0, gridBasis.getCol(0) * 3 + gridBasis.getCol(1));
        hexBasis.replaceCol(1, gridBasis.getCol(1) * 2);

        int start = 0;
        for (int i = 0; i < gridMapSize.y() / 2; i += 3)
        {
            start = this->hexesCount - i / 3 - 1;
            for (int j = start; j < gridMapSize.x() / 2; ++j)
            {
                if (std::abs(i % 2 - j % 2) != parity)
                {
                    const auto& firstPoint = gridBasis.getCol(0) * j +
                                             gridBasis.getCol(1) * (i + 1) -
                                             offset;
                    vertexPositionData.push_back(firstPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(firstPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& secondPoint = gridBasis.getCol(0) * (j + 1) +
                                              gridBasis.getCol(1) * i - offset;
                    vertexPositionData.push_back(secondPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(secondPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& thirdPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j) +
                        gridBasis.getCol(1) * (i + 1) - offset;
                    vertexPositionData.push_back(thirdPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(thirdPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& fourthPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j - 1) +
                        gridBasis.getCol(1) * i - offset;
                    vertexPositionData.push_back(fourthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(fourthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& fivethPoint =
                        gridBasis.getCol(0) * (j) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i - 1) -
                        offset;
                    vertexPositionData.push_back(fivethPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(fivethPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& sixthPoint =
                        gridBasis.getCol(0) * (j + 1) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
                    vertexPositionData.push_back(sixthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(sixthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& seventhPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i - 1) -
                        offset;
                    vertexPositionData.push_back(seventhPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(seventhPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& eightthPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j - 1) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
                    vertexPositionData.push_back(eightthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(eightthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                }
                else
                {
                    const auto& firstPoint = gridBasis.getCol(0) * j +
                                             gridBasis.getCol(1) * i - offset;
                    vertexPositionData.push_back(firstPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(firstPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& secondPoint = gridBasis.getCol(0) * (j + 1) +
                                              gridBasis.getCol(1) * (i + 1) -
                                              offset;
                    vertexPositionData.push_back(secondPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(secondPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& thirdPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j) +
                        gridBasis.getCol(1) * i - offset;
                    vertexPositionData.push_back(thirdPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(thirdPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& fourthPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j - 1) +
                        gridBasis.getCol(1) * (i + 1) - offset;
                    vertexPositionData.push_back(fourthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(fourthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& fivethPoint =
                        gridBasis.getCol(0) * j +
                        gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
                    vertexPositionData.push_back(fivethPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(fivethPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& sixthPoint =
                        gridBasis.getCol(0) * (j + 1) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i - 1) -
                        offset;
                    vertexPositionData.push_back(sixthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(sixthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);

                    const auto& seventhPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i) - offset;
                    vertexPositionData.push_back(seventhPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(seventhPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& eightthPoint =
                        gridBasis.getCol(0) * (gridMapSize.x() - j - 1) +
                        gridBasis.getCol(1) * (gridMapSize.y() - i - 1) -
                        offset;
                    vertexPositionData.push_back(eightthPoint.x() /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back(eightthPoint.y() /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
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

            for (int j = parity - i % 2; j < gridMapSize.x() + 1; j += 2)
            {
                if (j >= start && j <= gridMapSize.x() - start)
                {
                    const auto& firstPoint = gridBasis.getCol(0) * j +
                                             gridBasis.getCol(1) * i - offset;
                    vertexPositionData.push_back((firstPoint.x()) /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back((firstPoint.y()) /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
                    const auto& secondPoint = gridBasis.getCol(0) * j +
                                              gridBasis.getCol(1) * (i + 2) -
                                              offset;
                    vertexPositionData.push_back((secondPoint.x()) /
                                                 GAME_WINDOW_WIDTH);
                    vertexPositionData.push_back((secondPoint.y()) /
                                                 GAME_WINDOW_HEIGHT);
                    vertexPositionData.push_back(0.0);
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
};
