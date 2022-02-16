#include "shape_component.h"

ShapeComponent::ShapeComponent(const Shape& shape)
    : Shape(shape)
{
}

void ShapeComponent::SetShapeBufferIndex(
    const ShapeBufferIndex& shapeBufferIndex)
{
    this->positionDataIndex = shapeBufferIndex.GetPositionDataIndex();
    this->indexDataIndex    = shapeBufferIndex.GetIndexDataIndex();
    this->normalDataIndex   = shapeBufferIndex.GetNormalDataIndex();
    this->texCoordDataIndex = shapeBufferIndex.GetTexCoordDataIndex();
    this->colorDataIndex    = shapeBufferIndex.GetColorDataIndex();
}
