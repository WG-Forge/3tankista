#include "hex_shape.h"

HexShape::HexShape(const std::size_t size, const RenderingMode renderingMode)
    : IShape(renderingMode)
    , hexesCount(size)
    , hexMapSize(size, size)
{
    const auto& diagonal = hexMapSize.x() * 2 - 1;
    gridMapSize.x()      = diagonal * 3 + 1;
    gridMapSize.y()      = diagonal * 2;
}

ShapeID HexShape::GetShapeID() const
{
    std::size_t seed = hexMapSize.x();

    seed ^= (std::size_t)(static_cast<ShapeID>(SHAPE_TYPE) + 0x9e3779b9 + (seed << 6) + (seed >> 2));

    seed ^= (std::size_t)(this->hexMapSize.x() + 0x9e3779b9 + (seed << 6) + (seed >> 2));

    seed ^= (std::size_t)(this->GetRenderingMode() + 0x9e3779b9 + (seed << 6) + (seed >> 2));

    return seed;
}

bool HexShape::Initialize()
{

    vertexPositionData.clear();
    vertexNormalData.clear();
    vertexIndexData.clear();

    // for each hex
    // 1) get it's vertexes;
    // 2) add them to tree and create indexes
    std::vector<Vector3f> tmp;
    std::vector<Vector3f> hexVertexes;
    for (int i = -hexMapSize.x() + 1; i < hexMapSize.x(); ++i)
    {
        for (int j = -hexMapSize.x() - (i > 0 ? -1 : i - 1); j < (i > 0 ? hexMapSize.x() - i : hexMapSize.x()); ++j)
        {
            hexVertexes = this->GetVertHexVertices(Vector3i{ i, j, 0 });
            for (auto& vert : hexVertexes)
            {
                vert = Vector3f{ vert.x(), vert.y(), 0.0f };
            }
            this->vectorOfVertexes.push_back(hexVertexes);
            this->vertexesSet.insert(hexVertexes.begin(), hexVertexes.end());
        }
    }
    static constexpr float zCoordLines     = -0.1f;
    static constexpr float zCoordTriangles = 0.0f;

    std::vector<Vector3f> vector;
    vector.reserve(vertexesSet.size());
    for (auto it = vertexesSet.begin(); it != vertexesSet.end();)
    {
        vector.push_back(std::move(vertexesSet.extract(it++).value()));
        this->vertexPositionData.push_back(vector.back().x());
        this->vertexPositionData.push_back(vector.back().y());
        this->vertexPositionData.push_back(this->GetRenderingMode() == GL_LINES ? zCoordLines : zCoordTriangles);
    }

    // for each hex get vertexes and calculate indexes
    for (const auto& vertexes : vectorOfVertexes)
    {

        const auto& indexes = GetVertexesIndexes(vertexes, vector);

        this->GetRenderingMode() == GL_TRIANGLES ? GetTrianglesIndexes(indexes) : GetLinesIndexes(indexes);
    }

    this->vertexesCount  = vertexPositionData.size() / 3;
    this->trianglesCount = vertexIndexData.size() / 3;
    this->linesCount     = vertexIndexData.size() / 2;
    this->indexesCount   = vertexIndexData.size();

    return true;
}

std::vector<std::size_t> HexShape::GetVertexesIndexes(const std::vector<Vector3f>& vertexes,
                                                      const std::vector<Vector3f>& vector)
{
    std::vector<std::size_t> vertexesIndexes;
    vertexesIndexes.reserve(vertexes.size());
    for (const auto& v : vertexes)
    {
        auto vertex = std::find_if(vector.begin(), vector.end(), [&](const Vector3f& vertex) { return vertex == v; });
        std::size_t index = std::distance(vector.begin(), vertex);
        if (index == vector.size())
        {
            // invalid
            continue;
        }
        vertexesIndexes.emplace_back(std::move(index));
    }
    return vertexesIndexes;
}

void HexShape::GetLinesIndexes(const std::vector<std::size_t>& indexes)
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

void HexShape::GetTrianglesIndexes(const std::vector<std::size_t>& indexes)
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

Vector3f HexShape::Hex2Pixel(const Vector3i& hex)
{
    const auto& pixel = hex.x() * HEX_BASIS.getCol(0) + hex.y() * HEX_BASIS.getCol(1);
    return { pixel.x(), pixel.y(), -pixel.x() - pixel.y() };
}

std::vector<Vector3f> HexShape::GetVertHexVertices(const Vector3i& hex)
{
    const auto& pixel = Hex2Pixel(hex);
    return { pixel,
             pixel + 2 * Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 },
             pixel + Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                 Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
             pixel - Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
                 Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
             pixel - 2 * Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 },
             pixel - Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                 Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
             pixel + Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
                 Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 } };
}

std::vector<Vector3f> HexShape::GetHorHexVertices(const Vector3i& hex)
{
    const auto& pixel = Hex2Pixel(hex);
    return {
        pixel,
        pixel + Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
            Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
        pixel + Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
            Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
        pixel + 2 * Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
        pixel - Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } +
            Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
        pixel - Vector3f{ GRID_BASIS.getCol(0).x(), GRID_BASIS.getCol(0).y(), 0.0 } -
            Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
        pixel - 2 * Vector3f{ GRID_BASIS.getCol(1).x(), GRID_BASIS.getCol(1).y(), 0.0 },
    };
}
