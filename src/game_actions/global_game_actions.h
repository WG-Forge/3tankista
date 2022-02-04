#pragma once

#include "utility/matrix.hpp"
#include <string>

bool SendTurnAction();
bool SendChatAction(const std::string& message);
bool SendMoveAction(const int vehicleId, const Vector3i& target);
bool SendShootAction(const int vehicleId, const Vector3i& target);
