#include "default_material.h"

#include "utility/matrix_transform.h"

#include "game/game_configuration.h"

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

    Matrix4f projection =
        ortho(0.0f, static_cast<float>(GAME_WINDOW_WIDTH), static_cast<float>(GAME_WINDOW_HEIGHT), 0.0f);

    this->shader->Use();
    this->shader->SetMat4(PROJECTION_UNIFORM_NAME, projection);
    this->shader->Unuse();

    return true;
}

void DefaultMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
