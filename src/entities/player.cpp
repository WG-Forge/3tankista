#include "player.h"

Player::Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Player>(entityId, componentManager)
{
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(0);
    this->nameComponent          = AddComponent<NameComponent>(std::string{});
    this->killPointsComponent    = AddComponent<KillPointsComponent>(0);
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
    this->orderComponent         = AddComponent<OrderComponent>(0);
}

Player::Player(const ecs::EntityId&   entityId,
               ecs::ComponentManager* componentManager,
               const uint64_t         playerId,
               std::string            name)
    : GameObject<Player>(entityId, componentManager)
{
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(playerId);
    this->nameComponent          = AddComponent<NameComponent>(std::move(name));
    this->killPointsComponent    = AddComponent<KillPointsComponent>(0);
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
    this->orderComponent         = AddComponent<OrderComponent>(0);
}
