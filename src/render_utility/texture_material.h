#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include <memory>
//#include <unordered_map>

#include "imaterial.h"
#include "shader.hpp"

using TextureID = unsigned int;

class TextureMaterial : public IMaterial
{
public:
    TextureMaterial(const std::string& textureFileName);
    virtual ~TextureMaterial() = default;

public:
    static constexpr Type MATERIAL_TYPE{ Type::TEXTURE_MATERIAL };

    virtual inline const MaterialID GetMaterialID() const override
    {
        std::size_t seed = static_cast<MaterialID>(MATERIAL_TYPE);

        std::hash<std::string> hasher;

        seed ^= (std::size_t)(hasher(textureFileName) + 0x9e3779b9 +
                              (seed << 6) + (seed >> 2));

        return seed;
    }

    virtual void Use() const override;

    virtual void Unuse() const override;

    virtual bool Initialize() override;

    virtual void Release() override;

    virtual void SetModelTransform(const Matrix4f& model) override
    {
        if (this->shader != nullptr)
        {
            this->shader->SetMat4("aModelTransform", model);
        }
    }

    virtual void SetViewProjectionTransform(const Matrix4f& view,
                                            const Matrix4f& proj) override
    {
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
        return TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC;
    }

    virtual const MaterialVertexAttributeLoc GetColorVertexAttributeLocation()
        const override
    {
        return -1 /*COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC*/;
    }

    virtual void SetUniform4fv(const std::string& uniformName,
                               const Vector4f&    vec4) override
    {
        if (this->shader != nullptr)
        {
            this->shader->SetVec4(uniformName, vec4);
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
    std::string textureFileName;

    TextureID texture;

    std::unique_ptr<Shader> shader;
};

#endif // TEXTUREMATERIAL_H
