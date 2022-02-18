#pragma once

#include "shape.h"

//#include "log/logger.h"

#include <algorithm>
#include <cassert>
#include <vector>

class ShapeGenerator
{
    // NOTE: think about it

    using ShapeRegistry = std::vector<std::pair<IShape*, std::size_t>>;

public:
    ~ShapeGenerator();

    template <typename S>
    static Shape CreateShape(const std::size_t   size          = 0,
                             const RenderingMode renderingMode = GL_TRIANGLES)
    {
        ShapeGenerator& instance = ShapeGenerator::GetInstance();

        // check that shape not registered
        // for hex need check by type and size
        // for another only type
        auto it = std::find_if(
            instance.shapeRegistry.begin(),
            instance.shapeRegistry.end(),
            [&](const std::pair<IShape*, std::size_t>& shape)
            {
                return shape.first->GetShapeID() ==
                           static_cast<ShapeID>(S::SHAPE_TYPE) &&
                       shape.first->GetRenderingMode() == renderingMode &&
                       shape.second == size;
            });

        if (it != instance.shapeRegistry.cend())
        {
            return Shape(it->first);
        }

        IShape* shape = nullptr;
        if (size != 0)
        {
            shape = new S(size, renderingMode);
        }
        else
        {
            shape = new S(renderingMode);
        }

        bool isInitalized = shape->Initialize();
        assert((isInitalized == true) && "Failed to initialize shape!");

        // register new shape
        instance.shapeRegistry.push_back(std::make_pair(shape, size));

        return Shape(shape);
    }

private:
    ShapeGenerator();

    ShapeGenerator(const ShapeGenerator&) = delete;
    ShapeGenerator& operator=(const ShapeGenerator&) = delete;

private:
    static ShapeGenerator& GetInstance()
    {
        static ShapeGenerator instance;
        return instance;
    }

private:
    ShapeRegistry shapeRegistry;
};
