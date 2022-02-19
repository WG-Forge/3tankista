#ifndef LINEMATERIAL_H
#define LINEMATERIAL_H

#include "imaterial.h"
#include "shader.hpp"

class LineMaterial : public IMaterial
{
public:
    static constexpr Type MATERIAL_TYPE{ Type::LINE_MATERIAL };

    LineMaterial(const std::string& textureFileName);
    virtual ~LineMaterial();

    virtual inline const MaterialID GetMaterialID() const override
    {
        return static_cast<MaterialID>(MATERIAL_TYPE);
    }

    virtual void Use() const override;

    virtual void Unuse() const override;

    virtual bool Initialize() override;

    virtual void Release() override;

    virtual void SetModelTransform(const Matrix4f& model) override {}

    virtual void SetViewProjectionTransform(const Matrix4f& view,
                                            const Matrix4f& proj) override
    {
        //        if (this->shader != nullptr)
        //        {
        //            glUniformMatrix4fv(
        //                (*this->shader)(SHADER_UNIFORM_PROJECTION_TRANSFORM),
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
        return -1;
    }

    virtual const MaterialVertexAttributeLoc
    GetTexCoordVertexAttributeLocation() const override
    {
        return -1;
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
        //        if (this->shader != nullptr)
        //        {
        //            glUniformMatrix4fv((*this->shader)(uniformName),
        //                               1,
        //                               GL_FALSE,
        //                               (const GLfloat*)mat4);
        //        }
    }

private:
    std::unique_ptr<Shader> shader;
};

#endif // LINEMATERIAL_H
