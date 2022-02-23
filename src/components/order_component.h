#pragma once

#include "ecs.h"

class OrderComponent : public ecs::Component<OrderComponent>
{
public:
    explicit OrderComponent(const int order)
        : order(order)
    {
    }
    ~OrderComponent() override = default;

    auto GetOrder() const { return order; }
    void SetOrder(const int order) { this->order = order; }

private:
    int order;
};
