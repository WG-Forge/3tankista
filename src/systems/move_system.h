#pragma once

#include "components/hex_map_component.h"
#include "components/main_player_component.h"
#include "components/observer_component.h"
#include "components/order_component.h"
#include "components/transform_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "entities/map/map.h"
#include "game/game_events.h"
#include "utility/map_utility.h"
#include "win_system.h"
#include <algorithm>

class MoveSystem : public ecs::System<MoveSystem>, public ecs::event::IEventListener
{
public:
    MoveSystem();
    ~MoveSystem() override;

    void OnMoveResponse(const MoveResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
