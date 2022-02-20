#include "shape_generator.h"

ShapeGenerator::ShapeGenerator()
    : shapeRegistry()
{
}

ShapeGenerator::~ShapeGenerator()
{
    for (int i = 0; i < this->shapeRegistry.size(); ++i)
    {
        if (this->shapeRegistry[i].first != nullptr)
        {
            this->shapeRegistry[i].first->Release();
            delete this->shapeRegistry[i].first;
            this->shapeRegistry[i].first  = nullptr;
            this->shapeRegistry[i].second = 0;
        }
    }
}
