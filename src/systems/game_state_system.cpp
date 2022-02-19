#include "game_state_system.h"
#include "components//turn_component.h"
#include "components/adapter_player_id_component.h"
#include "components/name_component.h"
#include "components/ttc_factories/ttc_component_factory.h"
#include "entities/map/map.h"
#include "entities/player.h"
#include "entities/tank.h"
#include "entities/world.h"
#include <algorithm>

GameStateSystem::GameStateSystem()
{
    RegisterEventCallbacks();
}

GameStateSystem::~GameStateSystem()
{
    UnregisterEventCallbacks();
}

void GameStateSystem::OnGameStateResponseEvent(const GameStateResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto world            = ecs::ecsEngine->GetEntityManager()->GetEntity(
        ecs::ecsEngine->GetComponentManager()->begin<TurnComponent>()->GetOwner());
    world->GetComponent<TurnComponent>()->SetNumOfTurns(event->gameState.numberTurns);
    world->GetComponent<TurnComponent>()->SetCurrentTurn(event->gameState.currentTurn);
    auto adapterId = world->GetComponent<AdapterPlayerIdComponent>();
    auto vehicleId = world->GetComponent<AdapterVehicleIdComponent>();

    // Create players
    for (auto& now : event->gameState.players)
    {
        auto entity = entityManager->CreateEntity<Player>(now.idx, now.name);
        adapterId->Add(now.idx, entity);
        entityManager->GetEntity(entity)->GetComponent<PlayerIdComponent>()->SetPlayerId(entity);
    }
    world->GetComponent<CurrentPlayerComponent>()->SetCurrentPlayerId(
        adapterId->Get(event->gameState.currentPlayerIndex));

    // Create observers
    for (auto& now : event->gameState.observers)
    {
        auto entity = entityManager->CreateEntity<Player>(now.idx, now.name);
        adapterId->Add(now.idx, entity);
        entityManager->GetEntity(entity)->GetComponent<PlayerIdComponent>()->SetPlayerId(entity);
    }

    TtcComponentFactory factory;
    // Create tanks
    for (auto& tank : event->gameState.vehicles)
    {
        auto entity = entityManager->CreateEntity<Tank>(factory, tank.second.vehicleType);
        componentManager->GetComponent<PlayerIdComponent>(entity)->SetPlayerId(adapterId->Get(tank.second.playerId));
        componentManager->GetComponent<VehicleIdComponent>(entity)->SetVehicleId(entity);
        componentManager->GetComponent<SpawnPositionComponent>(entity)->SetSpawnPosition(tank.second.spawnPosition);
        componentManager->GetComponent<PositionComponent>(entity)->SetPosition(tank.second.position);
        componentManager->GetComponent<CapturePointsComponent>(entity)->SetCapturePoints(tank.second.capturePoints);
        vehicleId->Add(tank.first, entity);
    }
}

void GameStateSystem::OnWorldCreateEvent(const WorldCreateEvent* event)
{
    ecs::ecsEngine->GetEntityManager()->CreateEntity<World>();
}

void GameStateSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&GameStateSystem::OnGameStateResponseEvent);
    RegisterEventCallback(&GameStateSystem::OnWorldCreateEvent);
}

void GameStateSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&GameStateSystem::OnGameStateResponseEvent);
    UnregisterEventCallback(&GameStateSystem::OnWorldCreateEvent);
}
