#include "base.h"

Base::Base()
{
    this->baseId   = AddComponent<BaseIdComponent>();
    this->position = AddComponent<PositionComponent>(Vector3i(0, 0, 0));
}
