#pragma once

#include "buffers.h"

#include "render/materials/material.h"

#include "render/global.h"

#include <functional>

struct RenderableGroup
{
    const RenderableGroupID groupID;

    const VertexArray* vertexArray;

    Material material;

    RenderableGroup(const RenderableGroupID groupID)
        : groupID(groupID)
        , vertexArray(new VertexArray)
        , material(nullptr)
    {
    }

    RenderableGroup(const RenderableGroupID groupID, Material material)
        : groupID(groupID)
        , vertexArray(new VertexArray)
        , material(material)
    {
    }

    ~RenderableGroup() = default;

    void Delete() const { delete this->vertexArray; }

    bool operator==(const RenderableGroup& other) const { return this->groupID == other.groupID; }
};

namespace std
{
template <>
struct hash<RenderableGroup>
{
    std::size_t operator()(const RenderableGroup& renderableGroup) const { return renderableGroup.groupID; }
};
} // namespace std
