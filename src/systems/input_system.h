#pragma once

#include "ecs.h"

class InputSystem : public ecs::System<InputSystem>
{
public:
    InputSystem();
};
