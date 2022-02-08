#pragma once

#include "../third_party/ecs/src/ecs.h"

class InputSystem : public ecs::System<InputSystem>
{
public:
    InputSystem();
};
