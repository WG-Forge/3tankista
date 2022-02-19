#include "material_generator.h"

MaterialGenerator::MaterialGenerator()
    : materialRegistry()
{
}

MaterialGenerator::~MaterialGenerator()
{
    for (int i = 0; i < this->materialRegistry.size(); ++i)
    {
        if (this->materialRegistry[i].first != nullptr)
        {
            this->materialRegistry[i].first->Release();
            delete this->materialRegistry[i].first;
            this->materialRegistry[i].first = nullptr;
        }
    }
}
