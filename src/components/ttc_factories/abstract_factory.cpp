#include "abstract_factory.h"

TtcComponent* AbstractFactory::CreateTtc(GameObjectId id, const Ttc& ttc) const
{
    return ecs::ecsEngine->GetComponentManager()->AddComponent<TtcComponent>(id, ttc.speed, ttc.maxHealth, ttc.damage);
}
