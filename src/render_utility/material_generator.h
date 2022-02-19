#pragma once

#include "material.h"

#include <cassert>

class MaterialGenerator
{
    using MaterialRegistry = std::vector<std::pair<IMaterial*, std::string>>;

public:
    ~MaterialGenerator();

    template <typename M, typename... Args>
    static Material CreateMaterial(const std::string& textureFileName = "",
                                   Args&&... args)
    {
        MaterialGenerator& instance = MaterialGenerator::GetInstance();

        auto it = std::find_if(
            instance.materialRegistry.begin(),
            instance.materialRegistry.end(),
            [&](const std::pair<IMaterial*, std::string>& material)
            {
                return material.first->GetMaterialID() ==
                           static_cast<MaterialID>(M::MATERIAL_TYPE) &&
                       material.first->GetTextureFileName() == textureFileName;
            });

        if (it != instance.materialRegistry.cend())
        {
            return Material(it->first);
        }

        IMaterial* material = nullptr;
        material = new M(textureFileName, std::forward<Args>(args)...);

        bool isInitialized = material->Initialize();

        assert((isInitialized == true) && "Failed to initialize material!");

        instance.materialRegistry.push_back(
            std::make_pair(material, textureFileName));
        return Material(material);
    }

private:
    MaterialGenerator();

    MaterialGenerator(const MaterialGenerator&) = delete;
    MaterialGenerator& operator=(const MaterialGenerator&) = delete;

    static MaterialGenerator& GetInstance()
    {
        static MaterialGenerator instance;
        return instance;
    }

private:
    MaterialRegistry materialRegistry;
};
