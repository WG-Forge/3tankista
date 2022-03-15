#pragma once

#include "ecs.h"
#include "utility/matrix.hpp"
#include <string>

class NameComponent : public ecs::Component<NameComponent>
{
public:
    NameComponent() = default;
    explicit NameComponent(std::string name)
        : name(std::move(name))
    {
    }
    ~NameComponent() override = default;

public:
    void        SetName(std::string name) { this->name = std::move(name); }
    auto&       GetName() { return this->name; }
    const auto& GetName() const { return this->name; }

private:
    std::string name;
};
