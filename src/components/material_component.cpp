#include "material_component.h"

MaterialComponent::MaterialComponent(const Material& material, const Color& color)
    : Material(material)
    , color(color)
{
}

MaterialComponent::~MaterialComponent() {}

void MaterialComponent::Apply()
{
    // set uniform
    this->SetUniform4fv(COLOR_UNIFORM_NAME, color);
}

void MaterialComponent::SetColor(const float r, const float g, const float b, const float a)
{
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->color[3] = a;
}
