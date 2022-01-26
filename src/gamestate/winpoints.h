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
    void        SetCapture(const int& cup) { this->capture = cup; }
    auto&       GetCapture() { return this->capture; }
    const auto& GetCapture() const { return this->capture; }
    void        SetKill(const int& kp) { this->kill = kp; }
    auto&       GetKill() { return this->kill; }
    const auto& GetKill() const { return this->kill; }

private:
    int capture;
    int kill;
};
void to_json(nlohmann::json& j, const WinPoints& wp);

void from_json(const nlohmann::json& j, WinPoints& wp);

#endif // WINPOINTS_H
