#include "turn_system.h"
#include "components/turn_component.h"

TurnSystem::TurnSystem()
{
    DEFINE_LOGGER("TurnSystem")
    RegisterEventCallbacks();
}
TurnSystem::~TurnSystem()
{
    UnregisterEventCallbacks();
}

void TurnSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&TurnSystem::OnTurnResponseEvent);
}

void TurnSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&TurnSystem::OnTurnResponseEvent);
}

void TurnSystem::OnTurnResponseEvent(const TurnResponseEvent* event)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    std::cout << "Turn N " << componentManager->begin<TurnComponent>()->GetCurrentTurn() << "\n";
    LogInfo("Turn #%d", componentManager->begin<TurnComponent>()->GetCurrentTurn());
    componentManager->begin<TurnComponent>()->SetCurrentTurn(
        componentManager->begin<TurnComponent>()->GetCurrentTurn() + 1);
}
