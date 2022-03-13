#include "content.h"

Content::Content(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Content>(entityId, componentManager)
{
}
std::vector<Vector3i> Content::GetVectorV3i(std::vector<uint64_t> vectorId)
{
    auto                  entityManager = ecs::ecsEngine->GetEntityManager();
    std::vector<Vector3i> positionVector;
    positionVector.reserve(vectorId.size());
    for (auto id : vectorId)
    {
        positionVector.push_back(entityManager->GetEntity(id)->GetComponent<TransformComponent>()->GetPosition());
    }
    return positionVector;
}
