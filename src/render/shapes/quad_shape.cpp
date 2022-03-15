#include "quad_shape.h"

QuadShape::QuadShape(const std::size_t size, const RenderingMode renderingMode)
    : IShape(renderingMode)
{
}
bool QuadShape::Initialize()
{
    return true;
}
