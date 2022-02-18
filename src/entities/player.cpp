#include "player.h"

Player::Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Player>(entityId, componentManager)
{
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(0);
    this->killPointsComponent    = AddComponent<KillPointsComponent>(0);
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
}

Player::Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const int playerId)
    : GameObject<Player>(entityId, componentManager)
{
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(playerId);
    this->killPointsComponent    = AddComponent<KillPointsComponent>(0);
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
}
