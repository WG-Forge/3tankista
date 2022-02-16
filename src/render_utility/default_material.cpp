#include "default_material.h"

DefaultMaterial::DefaultMaterial()
    : shader(nullptr)
{
}

DefaultMaterial::~DefaultMaterial() {}

void DefaultMaterial::Use() const
{
    // activate shader program
    this->shader->Use();
}

void DefaultMaterial::Unuse() const
{
    glUseProgram(0);
}

bool DefaultMaterial::Initialize()
{
    this->shader = std::make_unique<Shader>("../shaders/default.vert",
                                            "../shaders/default.frag");
    //    this->shader = new Shader(
    //        new VertexShader(VERTEXT_SHADER), new
    //        FragmentShader(FRAGMENT_SHADER));
    //    return (this->shader->failed() == false &&
    //            this->shader->IsLinked());
    return true;
}

void DefaultMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
