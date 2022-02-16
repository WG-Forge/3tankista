#pragma once

#include "ecs.h"

#include "render_utility/material.h"

using Color = Vector4f;

class MaterialComponent : public Material,
                          public ecs::Component<MaterialComponent>
{

public:
    inline static const Color DEFAULT_COLOR0{ 0.8f, 0.8f, 8.0f, 1.0f };

public:
    MaterialComponent(const Material& material,
                      const Color&    color = DEFAULT_COLOR0);

    virtual ~MaterialComponent();

public:
    void Apply();

    inline void SetColor(const Color& color) { this->color = color; }
    void        SetColor(const float r,
                         const float g,
                         const float b,
                         const float a = 1.0f);

    inline const auto& GetColor() const { return this->color; }
    inline auto&       GetColor() { return this->color; }

private:
    Color color;
};
