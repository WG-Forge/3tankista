#pragma once

#include <cstdint>
#include <string>

#include "../utility/matrix.hpp"

using MaterialID                 = uint64_t;
using MaterialVertexAttributeLoc = uint32_t;

static constexpr MaterialID                 INVALID_MATERIAL_ID{ 0xffff };
static constexpr MaterialVertexAttributeLoc INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 0xffffffff };

static constexpr MaterialVertexAttributeLoc POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 0 };
static constexpr MaterialVertexAttributeLoc NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 1 };
static constexpr MaterialVertexAttributeLoc COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 2 };
static constexpr MaterialVertexAttributeLoc TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC{ 3 };

using ShapeID       = uint64_t;
using RenderingMode = unsigned int;

static constexpr ShapeID INVALID_SHAPE_ID{ 0xffff };

using RenderableGroupID = uint32_t;

inline static const std::string TRANSFORM_UNIFORM_NAME{ "uTransform" };
inline static const std::string PROJECTION_UNIFORM_NAME{ "uProjection" };
inline static const std::string COLOR_UNIFORM_NAME{ "uColor" };
inline static const std::string MIX_VALUE_UNIFORM_NAME{ "uMixValue" };

using Color = Vector4f;

inline static const Color WHITE_COLOR{ 1.0f, 1.0f, 1.0f, 1.0f };
