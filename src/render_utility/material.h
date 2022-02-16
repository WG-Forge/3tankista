#pragma once

#include "imaterial.h"

class Material
{
public:
    Material(IMaterial* material)
        : materialData(material)
    {
    }
    ~Material() { this->materialData = nullptr; }

    inline const MaterialID GetMaterialID() const
    {
        return this->materialData->GetMaterialID();
    }

    inline void Use() const
    {
        const_cast<IMaterial*>(this->materialData)->Use();
    }

    inline void Unuse() const
    {
        const_cast<IMaterial*>(this->materialData)->Unuse();
    }

    inline void SetModelTransform(const Matrix4f& model)
    {
        this->materialData->SetModelTransform(model);
    }

    inline void SetViewProjectionTransform(const Matrix4f& view,
                                           const Matrix4f& proj)
    {
        this->materialData->SetViewProjectionTransform(view, proj);
    };

    inline const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation()
        const
    {
        return this->materialData->GetPositionVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation()
        const
    {
        return this->materialData->GetNormalVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation()
        const
    {
        return this->materialData->GetTexCoordVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetColorVertexAttributeLocation()
        const
    {
        return this->materialData->GetColorVertexAttributeLocation();
    }

    inline void SetUniform4fv(const std::string& uniformName,
                              const Vector4f&    vec4)
    {
        this->materialData->SetUniform4fv(uniformName, vec4);
    }
    inline void SetUniformMatrix4fv(const std::string& uniformName,
                                    const Matrix4f&    mat4)
    {
        this->materialData->SetUniformMatrix4fv(uniformName, mat4);
    }

private:
    IMaterial* materialData;
};
