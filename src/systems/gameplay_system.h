#pragma once

#include "components/attack_matrix_component.h"
#include "components/hex_map_component.h"
#include "ecs.h"
#include "entities/tank.h"
#include "game/game_configuration.h"
#include "game/game_events.h"
#include "utility/matrix.hpp"

class GameplaySystem : public ecs::System<GameplaySystem>, public ecs::event::IEventListener
{
public:
    GameplaySystem();
    ~GameplaySystem() override;

    void OnPlayEvent(const PlayEvent* event);

    struct Context
    {
        std::vector<Tank*>     friends;
        std::vector<Tank*>     enemies;
        AttackMatrixComponent* attackMatrix;
        HexMapComponent*       hexMap;
    };

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
