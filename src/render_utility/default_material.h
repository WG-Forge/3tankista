#pragma once

#include <memory>

#include "imaterial.h"
#include "shader.hpp"

class DefaultMaterial : public IMaterial
{
public:
    DefaultMaterial();
    virtual ~DefaultMaterial();

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
            shader->SetMat4("aModelTransform", model);
        }
    }

    virtual void SetViewProjectionTransform(const Matrix4f& view,
                                            const Matrix4f& proj) override
    {
        //        if (this->shader != nullptr)
        //        {
        //            glUniformMatrix4fv(
        //                (*this->m_ShaderProgram)(SHADER_UNIFORM_VIEW_TRANSFORM),
        //                1,
        //                GL_FALSE,
        //                (const GLfloat*)view);
        //            glUniformMatrix4fv(
        //                (*this->m_ShaderProgram)(SHADER_UNIFORM_PROJECTION_TRANSFORM),
        //                1,
        //                GL_FALSE,
        //                (const GLfloat*)proj);
        //        }
    }

    virtual const MaterialVertexAttributeLoc
    GetPositionVertexAttributeLocation() const override
    {
        return POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation()
        const override
    {
        return -1 /*NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC*/;
    }

    virtual const MaterialVertexAttributeLoc
    GetTexCoordVertexAttributeLocation() const override
    {
        return -1 /*TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC*/;
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

private:
    std::unique_ptr<Shader> shader;
};
