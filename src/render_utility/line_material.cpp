#include "line_material.h"

LineMaterial::LineMaterial()
    : shader(nullptr)
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
        std::make_unique<Shader>("/home/vlad/game_dev/wg_forge/wot_strategy/"
                                 "build-3tankista-Desktop_Qt_5_15_2_GCC_64bit-"
                                 "Debug/src/shaders/line.vert",
                                 "/home/vlad/game_dev/wg_forge/wot_strategy/"
                                 "build-3tankista-Desktop_Qt_5_15_2_GCC_64bit-"
                                 "Debug/src/shaders/line.frag");
    //    return (this->shader->failed() == false && this->shader->IsLinked());
    return true;
}

void LineMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
