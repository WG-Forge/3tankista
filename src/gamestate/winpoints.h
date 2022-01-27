//
// Created by serge on 26.01.22.
//

#ifndef WINPOINTS_H
#define WINPOINTS_H
#include "nlohmann/json.hpp"

class WinPoints
{
public:
    WinPoints();

public:
    void        SetCapture(const int& cupture) { this->capture = cupture; }
    auto&       GetCapture() { return this->capture; }
    const auto& GetCapture() const { return this->capture; }
    void        SetKill(const int& kill) { this->kill = kill; }
    auto&       GetKill() { return this->kill; }
    const auto& GetKill() const { return this->kill; }

private:
    int capture;
    int kill;
};
void to_json(nlohmann::json& json, const WinPoints& winPoints);

void from_json(const nlohmann::json& json, WinPoints& winPoints);

#endif // WINPOINTS_H
