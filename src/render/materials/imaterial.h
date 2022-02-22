#pragma once

#include <cstdint>
#include <string>

#include "utility/matrix.hpp"

using MaterialID                 = uint16_t;
using MaterialVertexAttributeLoc = uint32_t;

static constexpr MaterialID                 INVALID_MATERIAL_ID{ 0xffff };
static constexpr MaterialVertexAttributeLoc INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 0xffffffff };

static constexpr MaterialVertexAttributeLoc POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 0 };
static constexpr MaterialVertexAttributeLoc NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 1 };
static constexpr MaterialVertexAttributeLoc COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 2 };
static constexpr MaterialVertexAttributeLoc TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 3 };

inline static const std::string TRANSFORM_UNIFORM_NAME{ "uTransform" };
inline static const std::string PROJECTION_UNIFORM_NAME{ "uProjection" };
inline static const std::string COLOR_UNIFORM_NAME{ "uColor" };
inline static const std::string MIX_VALUE_UNIFORM_NAME{ "uMixValue" };

class IMaterial
{
public:
    enum class Type
    {
        INVALID_MATERIAL = INVALID_MATERIAL_ID,
        DEFAULT_MATERIAL = 0,
        LINE_MATERIAL    = 1,
        TEXTURE_MATERIAL = 2,
        MAX_MATERIALS
    };

    IMaterial(const std::string& textureFileName = "")
        : textureFileName(textureFileName)
    {
    }
    virtual ~IMaterial() = default;

    virtual inline const MaterialID GetMaterialID() const { return INVALID_MATERIAL_ID; }

    virtual void Use() const = 0;

    virtual void Unuse() const = 0;

    virtual bool Initialize() = 0;

    virtual void Release() = 0;

    virtual void SetModelTransform(const Matrix4f& model) = 0;

    virtual void SetProjectionTransform(const Matrix4f& model) = 0;

    virtual void SetViewProjectionTransform(const Matrix4f& view, const Matrix4f& proj) = 0;

    virtual const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const = 0;

    virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const = 0;

    virtual const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const = 0;

    virtual const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const = 0;

    virtual void SetUniform4fv(const std::string& uniformName, const Vector4f& vec4)       = 0;
    virtual void SetUniformMatrix4fv(const std::string& uniformName, const Matrix4f& mat4) = 0;

    virtual void SetUniform1f(const std::string& uniformName, const float value) = 0;

    auto GetTextureFileName() { return this->textureFileName; }

    const auto GetTextureFileName() const { return this->textureFileName; }

private:
    void SetTextureFileName(const unsigned int) = delete;

private:
    std::string textureFileName;
};
