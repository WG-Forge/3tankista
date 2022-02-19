#include "line_material.h"

LineMaterial::LineMaterial(const std::string& textureFileName)
    : IMaterial(textureFileName)
    , shader(nullptr)
{
}

LineMaterial::~LineMaterial() {}

void LineMaterial::Use() const
{
    this->shader->Use();
}

void LineMaterial::Unuse() const
{
    this->shader->Unuse();
}

bool LineMaterial::Initialize()
{
    this->shader =
        std::make_unique<Shader>("shaders/line.vert", "shaders/line.frag");
    //    return (this->shader->failed() == false && this->shader->IsLinked());
    return true;
}

void LineMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
