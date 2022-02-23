#pragma once

#include "render/shapes/ishape.h"

class Shape
{
public:
    Shape(const IShape* shapeData)
        : shapeImpl(shapeData)
    {
    }
    virtual ~Shape() { this->shapeImpl = nullptr; }

    inline const ShapeID GetShapeID() const { return this->shapeImpl->GetShapeID(); }

    inline bool IsValid() const { return this->shapeImpl != nullptr; }

    inline const std::size_t GetVertexesCount() const { return this->shapeImpl->GetVertexesCount(); }

    inline const std::size_t GetTrianglesCount() const { return this->shapeImpl->GetTrianglesCount(); }

    inline const std::size_t GetLinesCount() const { return this->shapeImpl->GetLinesCount(); }

    inline const std::size_t GetIndexesCount() const { return this->shapeImpl->GetIndexesCount(); }

    inline const bool IsIndexed() const { return this->GetIndexes() != nullptr; }

    inline const VertexPositionData* GetPositions() const { return this->shapeImpl->GetPositions(); }

    inline const VertexIndexData* GetIndexes() const { return this->shapeImpl->GetIndexes(); }

    inline const VertexNormalData* GetNormals() const { return this->shapeImpl->GetNormals(); }

    inline const VertexTexCoordData* GetTexCoords() const { return this->shapeImpl->GetTexCoords(); }

    inline const VertexColorData* GetColors() const { return this->shapeImpl->GetColors(); }

    auto       GetRenderingMode() { return this->shapeImpl->GetRenderingMode(); }
    const auto GetRenderingMode() const { return this->shapeImpl->GetRenderingMode(); }

private:
    void SetRenderingMode(const unsigned int) = delete;

private:
    const IShape* shapeImpl;
};
