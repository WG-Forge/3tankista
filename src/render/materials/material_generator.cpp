#include "material_generator.h"

MaterialGenerator::MaterialGenerator()
    : materialRegistry(static_cast<std::size_t>(IMaterial::Type::MAX_MATERIALS), nullptr)
{
}

MaterialGenerator::~MaterialGenerator()
{
    for (int i = 0; i < this->materialRegistry.size(); ++i)
    {
        if (this->materialRegistry[i] != nullptr)
        {
            this->materialRegistry[i]->Release();
            delete this->materialRegistry[i];
            this->materialRegistry[i] = nullptr;
        }
    }
}
