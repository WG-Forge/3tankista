#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "models/content.h"
#include "models/spawn_points.h"

// TODO: rework hard and light repair, and tank spawn point.
//       try to do this with base classes (think about problem of type).

class Map
{
public:
    Map();

public:
    void        SetSize(const std::size_t& size) { this->size = size; }
    auto&       GetSize() { return this->size; }
    const auto& GetSize() const { return this->size; }

    void        SetName(const std::string& name) { this->name = name; }
    auto&       GetName() { return this->name; }
    const auto& GetName() const { return this->name; }

    void SetSpawnPoints(const std::vector<SpawnPoints>& spawnPoints)
    {
        this->spawnPoints = spawnPoints;
    }
    auto&       GetSpawnPoints() { return this->spawnPoints; }
    const auto& GetSpawnPoints() const { return this->spawnPoints; }

    void        SetContent(const Content& content) { this->content = content; }
    auto&       GetContent() { return this->content; }
    const auto& GetContent() const { return this->content; }

private:
    uint64_t                 size;
    std::string              name;
    std::vector<SpawnPoints> spawnPoints;
    Content                  content;
};

void to_json(nlohmann::json& json, const Map& map);

void from_json(const nlohmann::json& json, Map& map);

