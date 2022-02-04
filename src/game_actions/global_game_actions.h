#pragma once

#include <string>

#include "utility/matrix.hpp"

bool SendTurnAction();
bool SendChatAction(const std::string& message);
bool SendMoveAction(const int vehicleId, const Vector3i& target);
bool SendShootAction(const int vehicleId, const Vector3i& target);
