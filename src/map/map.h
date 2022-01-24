#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <string>
#include <vector>

#include "content.h"
#include "spawnpoints.h"

class Map
{
public:
    Map();

private:
    void        SetSize(const std::size_t& size) { this->size = size; }
    auto&       GetSize() { return this->size; }
    const auto& GetSize() const { return this->size; }

    void        SetName(const std::string& name) { this->name = name; }
    auto&       GetName() { return this->name; }
    const auto& GetName() const { return this->name; }

    void        SetContent(const Content& content) { this->content = content; }
    auto&       Getcontent() { return this->content; }
    const auto& Getcontent() const { return this->content; }

    void SetSpawnPoints(const SpawnPoints& spawnPoints)
    {
        this->spawnPoints = spawnPoints;
    }
    auto&       GetSpawnPoints() { return this->spawnPoints; }
    const auto& GetSpawnPoint() const { return this->spawnPoints; }

private:
    uint64_t    size;
    std::string name;
    Content     content;
    SpawnPoints spawnPoints;
};

#endif // MAP_H
