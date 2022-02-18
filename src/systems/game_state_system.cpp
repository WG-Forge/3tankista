#include "game_state_system.h"
#include "components//turn_component.h"
#include "components/adapter_player_id_component.h"
#include "components/ttc_factories/ttc_component_factory.h"
#include "entities/player.h"
#include "entities/tank.h"
#include "entities/world.h"

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
    world->GetComponent<CurrentPlayerComponent>()->SetCurrentPlayerId(event->gameState.currentPlayerIndex);
    world->GetComponent<TurnComponent>()->SetCurrentTurn(event->gameState.currentTurn);
    auto adapterId = world->GetComponent<AdapterPlayerIdComponent>();
    auto vehicleId = world->GetComponent<AdapterVehicleIdComponent>();

    // Create players
    for (auto& now : event->gameState.players)
    {
        auto entity = entityManager->CreateEntity<Player>(now.idx);
        adapterId->Add(now.idx, entity);
    }

    // Create observers
    for (auto& now : event->gameState.observers)
    {
        auto entity = entityManager->CreateEntity<Player>(now.idx);
    }

    TtcComponentFactory factory;

    // Create tanks
    for (auto& tank : event->gameState.vehicles)
    {
        auto entity = entityManager->CreateEntity<Tank>(factory, tank.second.vehicleType);
        componentManager->GetComponent<PlayerIdComponent>(entity)->SetPlayerId(tank.second.playerId);
        componentManager->GetComponent<VehicleIdComponent>(entity)->SetVehicleId(tank.first);
        componentManager->GetComponent<SpawnPositionComponent>(entity)->SetSpawnPosition(tank.second.spawnPosition);
        componentManager->GetComponent<PositionComponent>(entity)->SetPosition(tank.second.position);
        componentManager->GetComponent<CapturePointsComponent>(entity)->SetCapturePoints(tank.second.capturePoints);
        vehicleId->Add(tank.first, entity);
    }
}

void GameStateSystem::OnGameFinishedRequestEvent(const GameFinishedRequestEvent* event)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto end              = componentManager->end<KillPointsComponent>();
    auto begin            = componentManager->begin<KillPointsComponent>();
    if (!componentManager->begin<TurnComponent>()->isFinished())
    {
        for (auto it = componentManager->begin<KillPointsComponent>();
             componentManager->end<KillPointsComponent>() != it;
             ++it)
        {
            if (entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints() >=
                5)
            {
                ecs::ecsEngine->SendEvent<GameFinishedResponseEvent>(true);
                break;
            }
        }
        ecs::ecsEngine->SendEvent<GameFinishedResponseEvent>(false);
    }
    else
    {
        ecs::ecsEngine->SendEvent<GameFinishedResponseEvent>(true);
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
    RegisterEventCallback(&GameStateSystem::OnGameFinishedRequestEvent);
}

void GameStateSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&GameStateSystem::OnGameStateResponseEvent);
    UnregisterEventCallback(&GameStateSystem::OnWorldCreateEvent);
    UnregisterEventCallback(&GameStateSystem::OnGameFinishedRequestEvent);
}
