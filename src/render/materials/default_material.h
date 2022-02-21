#pragma once

#include <memory>

#include "render/materials/imaterial.h"
#include "render/utility/shader.hpp"

class DefaultMaterial : public IMaterial
{
public:
    DefaultMaterial();
    virtual ~DefaultMaterial() = default;

public:
    static constexpr Type MATERIAL_TYPE{ Type::DEFAULT_MATERIAL };

    virtual inline const MaterialID GetMaterialID() const override
    {
        return static_cast<MaterialID>(MATERIAL_TYPE);
    }

    virtual void Use() const override;

    virtual void Unuse() const override;

    virtual bool Initialize() override;

    virtual void Release() override;

    virtual void SetModelTransform(const Matrix4f& model) override
    {
        if (this->shader != nullptr)
        {
            shader->SetMat4(MODEL_TRANSFORM_UNIFORM_NAME, model);
        }
    }

    virtual void SetViewProjectionTransform(const Matrix4f& view,
                                            const Matrix4f& proj) override
    {
        // TODO: add camera and view-projection matrixes
    }

    virtual const MaterialVertexAttributeLoc
    GetPositionVertexAttributeLocation() const override
    {
        return POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation()
        const override
    {
        return NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual const MaterialVertexAttributeLoc
    GetTexCoordVertexAttributeLocation() const override
    {
        return TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual const MaterialVertexAttributeLoc GetColorVertexAttributeLocation()
        const override
    {
        return COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual void SetUniform4fv(const std::string& uniformName,
                               const Vector4f&    vec4) override
    {
        if (this->shader != nullptr)
        {
            shader->SetVec4(uniformName, vec4);
        }
    }

    virtual void SetUniformMatrix4fv(const std::string& uniformName,
                                     const Matrix4f&    mat4) override
    {
        if (this->shader != nullptr)
        {
            //            glUniformMatrix4fv((*this->m_ShaderProgram)(uniformName),
            //                               1,
            //                               GL_FALSE,
            //                               (const GLfloat*)mat4);
        }
    }

    inline void SetUniform1f(const std::string& uniformName, const float value)
    {
        if (this->shader != nullptr)
        {
            shader->SetFloat(uniformName, value);
        }
    }

private:
    std::unique_ptr<Shader> shader;
};
