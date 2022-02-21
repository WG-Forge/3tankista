#include "transform_component.h"

TransformComponent::TransformComponent(const Vector3i& position)
    : transform(Vector3f(position.x(), position.y(), position.z()))
{
}

TransformComponent::TransformComponent(const Matrix4f& transform)
    : transform(transform)
{
}

TransformComponent::TransformComponent(const Transform& transform)
    : transform(transform)
{
}
