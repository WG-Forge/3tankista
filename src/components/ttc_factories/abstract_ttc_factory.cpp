#include "abstract_ttc_factory.h"

TtcComponent* AbstractTtcFactory::CreateTtc(GameObjectId id, const Ttc& ttc) const
{
    return ecs::ecsEngine->GetComponentManager()->AddComponent<TtcComponent>(
        id, ttc.speed, ttc.maxHealth, ttc.damage, ttc.standartRange);
}
