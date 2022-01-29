#ifndef GLOBALGAMEACTIONS_H
#define GLOBALGAMEACTIONS_H

#include <string>

#include "matrix.hpp"

bool SendTurnAction();
bool SendChatAction(const std::string& message);
bool SendMoveAction(const int vehicleId, const Vector3i& target);
bool SendShootAction(const int vehicleId, const Vector3i& target);

#endif // GLOBALGAMEACTIONS_H
