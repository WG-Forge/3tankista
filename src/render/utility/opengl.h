#pragma once

#include "glad.h"

#include "GLFW/glfw3.h"

#include <string>

using VertexPositionData = GLfloat;
using VertexIndexData    = GLushort;
using VertexNormalData   = GLfloat;
using VertexTexCoordData = GLfloat;
using VertexColorData    = GLfloat;

static constexpr GLenum VERTEX_POSITION_DATA_TYPE{ GL_FLOAT };
static constexpr GLenum VERTEX_INDEX_DATA_TYPE{ GL_UNSIGNED_SHORT };
static constexpr GLenum VERTEX_NORMAL_DATA_TYPE{ GL_FLOAT };
static constexpr GLenum VERTEX_TEXCOORD_DATA_TYPE{ GL_FLOAT };
static constexpr GLenum VERTEX_COLOR_DATA_TYPE{ GL_FLOAT };

static constexpr size_t VERTEX_POSITION_DATA_ELEMENT_LEN{ 3 };
static constexpr size_t VERTEX_INDEX_DATA_ELEMENT_LEN{ 1 };
static constexpr size_t VERTEX_NORMAL_DATA_ELEMENT_LEN{ 3 };
static constexpr size_t VERTEX_TEXCOORD_DATA_ELEMENT_LEN{ 2 };
static constexpr size_t VERTEX_COLOR_DATA_ELEMENT_LEN{ 3 };

static constexpr size_t VERTEX_POSITION_DATA_ELEMENT_SIZE{
    VERTEX_POSITION_DATA_ELEMENT_LEN * sizeof(VertexPositionData)
};
static constexpr size_t VERTEX_INDEX_DATA_ELEMENT_SIZE{
    VERTEX_INDEX_DATA_ELEMENT_LEN * sizeof(VertexIndexData)
};
static constexpr size_t VERTEX_NORMAL_DATA_ELEMENT_SIZE{
    VERTEX_NORMAL_DATA_ELEMENT_LEN * sizeof(VertexNormalData)
};
static constexpr size_t VERTEX_TEXCOORD_DATA_ELEMENT_SIZE{
    VERTEX_TEXCOORD_DATA_ELEMENT_LEN * sizeof(VertexTexCoordData)
};
static constexpr size_t VERTEX_COLOR_DATA_ELEMENT_SIZE{
    VERTEX_COLOR_DATA_ELEMENT_LEN * sizeof(VertexColorData)
};
