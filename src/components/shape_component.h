#pragma once

#include <ecs.h>

#include "render_utility/shape.h"
#include "render_utility/shape_buffer_index.h"

class ShapeComponent : public Shape,
                       public ShapeBufferIndex,
                       public ecs::Component<ShapeComponent>
{
    friend class RenderSystem;

public:
    ShapeComponent(const Shape& shape);

    virtual ~ShapeComponent() = default;

private:
    void SetShapeBufferIndex(const ShapeBufferIndex& shapeBufferIndex);
};
