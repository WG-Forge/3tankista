#pragma once

#include "components/base_id_component.h"
#include "components/position_component.h"
#include "game/game_object.h"

class Base : GameObject<Base>
{
public:
    Base();
    ~Base() override = default;

private:
    BaseIdComponent*   baseId;
    PositionComponent* position;
};
