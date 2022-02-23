#pragma once

#include "render/materials/imaterial.h"

class Material
{
public:
    Material(IMaterial* material)
        : materialImpl(material)
    {
    }
    ~Material() { this->materialImpl = nullptr; }

    inline const MaterialID GetMaterialID() const { return this->materialImpl->GetMaterialID(); }

    inline void Use() const { const_cast<IMaterial*>(this->materialImpl)->Use(); }

    inline void Unuse() const { const_cast<IMaterial*>(this->materialImpl)->Unuse(); }

    inline void SetModelTransform(const Matrix4f& model) { this->materialImpl->SetModelTransform(model); }

    inline void SetProjectionTransform(const Matrix4f& model) { this->materialImpl->SetProjectionTransform(model); }

    inline void SetViewProjectionTransform(const Matrix4f& view, const Matrix4f& proj)
    {
        this->materialImpl->SetViewProjectionTransform(view, proj);
    };

    inline const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const
    {
        return this->materialImpl->GetPositionVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const
    {
        return this->materialImpl->GetNormalVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const
    {
        return this->materialImpl->GetTexCoordVertexAttributeLocation();
    }

    inline const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const
    {
        return this->materialImpl->GetColorVertexAttributeLocation();
    }

    inline void SetUniform4fv(const std::string& uniformName, const Vector4f& vec4)
    {
        this->materialImpl->SetUniform4fv(uniformName, vec4);
    }
    inline void SetUniformMatrix4fv(const std::string& uniformName, const Matrix4f& mat4)
    {
        this->materialImpl->SetUniformMatrix4fv(uniformName, mat4);
    }

    inline void SetUniform1f(const std::string& uniformName, const float value)
    {
        this->materialImpl->SetUniform1f(uniformName, value);
    }

    auto       GetTextureFileName() { return this->materialImpl->GetTextureFileName(); }
    const auto GetTextureFileName() const { return this->materialImpl->GetTextureFileName(); }

private:
    void SetTextureFileName(const unsigned int) = delete;

private:
    IMaterial* materialImpl;
};
