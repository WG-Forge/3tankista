#include "game_state_system.h"
#include "entities/player.h"
#include "entities/tank.h"
#include "components/ttc_factories/ttc_component_factory.h"

GameStateSystem::GameStateSystem()
{
    RegisterEventCallbacks();
}

GameStateSystem::~GameStateSystem()
{
    UnregisterEventCallbacks();
}

void GameStateSystem::OnGameStateResponceEvent(
    const GameStateResponceEvent* event)
{
    auto entityManager = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    // Create players
    for (auto& now : event->gameState.players) {
        auto entity = entityManager->CreateEntity<Player>(now.idx);
    }

    // Create observers
    for (auto& now : event->gameState.observers) {
        auto entity = entityManager->CreateEntity<Player>(now.idx);
    }

    TtcComponentFactory factory;

    // Create tanks
    for (auto& tank : event->gameState.vehicles) {
        auto entity = entityManager->CreateEntity<Tank>(factory, tank.second.vehicleType);
        componentManager->GetComponent<PlayerIdComponent>(entity)->SetPlayerId(tank.second.playerId);
        componentManager->GetComponent<VehicleIdComponent>(entity)->SetVehicleId(tank.first);
        componentManager->GetComponent<SpawnPositionComponent>(entity)->SetSpawnPosition(tank.second.spawnPosition);
        componentManager->GetComponent<PositionComponent>(entity)->SetPosition(tank.second.position);
        // TODO: WinPoints component in tank entity, but we have only capture points
        auto winPointsComponent = componentManager->GetComponent<WinPointsComponent>(entity);
        winPointsComponent->SetCapturePoints(tank.second.capturePoints);
    }
}

void GameStateSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&GameStateSystem::OnGameStateResponceEvent);
}

void GameStateSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&GameStateSystem::OnGameStateResponceEvent);
}
