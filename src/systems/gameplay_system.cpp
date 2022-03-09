#include "gameplay_system.h"
#include "components/attack_matrix_component.h"
#include "components/main_player_component.h"
#include "components/observer_component.h"
#include "components/order_component.h"
#include "components/states/abstract_state.h"
#include "components/turn_component.h"
#include "entities/map/content.h"
#include "entities/map/map.h"
#include "entities/tank.h"
#include "utility/map_utility.h"
#include "win_system.h"
#include <queue>

GameplaySystem::GameplaySystem()
{
    RegisterEventCallbacks();
}

GameplaySystem::~GameplaySystem()
{
    UnregisterEventCallbacks();
}

void GameplaySystem::OnPlayEvent(const PlayEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto gameArea         = componentManager->begin<HexMapComponent>().operator->();
    auto mainPlayerId     = componentManager->begin<MainPlayerComponent>()->GetMainPlayerId();
    auto turnComponent    = componentManager->begin<TurnComponent>().operator->();
    auto attackMatrix     = componentManager->begin<AttackMatrixComponent>().operator->();

    if(turnComponent->GetCurrentTurn()==9){
        int a=5;
    }
    uint64_t currentPlayerId;
    for (auto it = componentManager->begin<OrderComponent>(); componentManager->end<OrderComponent>() != it; ++it)
    {
        if (it->GetOrder() == turnComponent->GetCurrentTurn() % turnComponent->GetPlayersNumber())
        {
            currentPlayerId = it->GetOwner();
        }
    }

    if (mainPlayerId == currentPlayerId &&
        !entityManager->GetEntity(mainPlayerId)->GetComponent<ObserverComponent>()->GetIsObserver())
    {
        std::vector<Tank*> currentPlayerTanks;
        std::vector<Tank*> enemies;
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto tank = (Tank*)entityManager->GetEntity(it->GetVehicleId());
            if (tank->GetComponent<PlayerIdComponent>()->GetPlayerId() == mainPlayerId)
            {
                currentPlayerTanks.push_back(tank);
            }
            else
            {
                enemies.push_back(tank);
            }
        }
        std::sort(currentPlayerTanks.begin(),
                  currentPlayerTanks.end(),
                  [](Tank* lhs, Tank* rhs)
                  {
                      return lhs->GetComponent<TankTypeComponent>()->GetTankType() <
                             rhs->GetComponent<TankTypeComponent>()->GetTankType();
                  });

        Context gameplayContext = { currentPlayerTanks, enemies, attackMatrix, gameArea };
        for (auto tank : currentPlayerTanks)
        {
            auto state = tank->GetComponent<StateComponent>();
            state->GetState()->UpdateState(gameplayContext);
            state->GetState()->Play(gameplayContext);
        }
    }
    attackMatrix->ClearUserAttacks(currentPlayerId);
    ecs::ecsEngine->SendEvent<TurnRequestEvent>();
    ecs::ecsEngine->SendEvent<GameActionsRequestEvent>();
}

void GameplaySystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&GameplaySystem::OnPlayEvent);
}

void GameplaySystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&GameplaySystem::OnPlayEvent);
}
