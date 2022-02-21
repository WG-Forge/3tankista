#pragma once

#include "ecs.h"

class ObserverComponent : public ecs::Component<ObserverComponent>
{
public:
    explicit ObserverComponent(const bool isObserver)
        : isObserver(isObserver)
    {
    }
    ~ObserverComponent() override = default;

public:
    void SetIsObserver(const bool isObserver) { this->isObserver = isObserver; }
    auto GetIsObserver() const { return this->isObserver; }

private:
    bool isObserver;
};
