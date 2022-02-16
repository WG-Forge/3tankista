#pragma once

#include "material.h"

#include <cassert>

class MaterialGenerator
{
    using MaterialRegistry = std::vector<IMaterial*>;

public:
    ~MaterialGenerator();

    template <typename M>
    static Material CreateMaterial()
    {
        MaterialGenerator& instance = MaterialGenerator::GetInstance();

        IMaterial* material = nullptr;

        material =
            instance
                .materialRegistry[static_cast<MaterialID>(M::MATERIAL_TYPE)];

        if (material != nullptr)
        {
            return Material(material);
        }

        material = new M;

        bool isInitialized = material->Initialize();

        assert((isInitialized == true) && "Failed to initialize material!");

        instance.materialRegistry[static_cast<MaterialID>(M::MATERIAL_TYPE)] =
            material;

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
