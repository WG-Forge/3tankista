#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "models/content.h"
#include "models/spawn_points.h"

class Map
{
public:
    Map()          = default;
    virtual ~Map() = default;

public:
    void SetSize(const std::size_t& size) { this->size = size; }
    auto GetSize() const { return this->size; }

    void        SetName(std::string& name) { this->name = std::move(name); }
    auto&       GetName() { return this->name; }
    const auto& GetName() const { return this->name; }

    void SetSpawnPoints(std::vector<SpawnPoints>& spawnPoints)
    {
        this->spawnPoints = std::move(spawnPoints);
    }
    auto&       GetSpawnPoints() { return this->spawnPoints; }
    const auto& GetSpawnPoints() const { return this->spawnPoints; }

    void  SetContent(Content& content) { this->content = std::move(content); }
    auto& GetContent() { return this->content; }
    const auto& GetContent() const { return this->content; }

private:
    uint64_t                 size;
    std::string              name;
    std::vector<SpawnPoints> spawnPoints;
    Content                  content;
};

void to_json(nlohmann::json& json, const Map& map);

void from_json(const nlohmann::json& json, Map& map);
