#include "default_material.h"

DefaultMaterial::DefaultMaterial()
    : IMaterial()
    , shader(nullptr)
{
}

void DefaultMaterial::Use() const
{
    // activate shader program
    this->shader->Use();
}

void DefaultMaterial::Unuse() const
{
    this->shader->Unuse();
}

bool DefaultMaterial::Initialize()
{
    this->shader = std::make_unique<Shader>("shaders/default.vert", "shaders/default.frag");
    return true;
}

void DefaultMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
