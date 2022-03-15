#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "ecs.h"

#include "transform.h"

class TransformComponent : public ecs::Component<TransformComponent>
{
public:
    TransformComponent() = default;
    TransformComponent(const Vector3i& position);
    TransformComponent(const Matrix4f& transform);
    TransformComponent(const Transform& transform);

    virtual ~TransformComponent() = default;

    inline void SetTransform(const Matrix4f& transform) { this->transform = (Transform)transform; }

    inline auto        GetPosition() { return this->transform.GetPosition(); }
    void               SetPosition(const Vector3i& position) { this->transform.SetPosition(position); }
    inline auto&       GetTransform() { return this->transform; }
    inline const auto& GetTransform() const { return this->transform; }

private:
    Transform transform;
};

#endif // TRANSFORMCOMPONENT_H
