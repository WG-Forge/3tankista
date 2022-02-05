#include "action_data.h"

ActionData::ActionData(const int vehicleId, const Vector3i& target)
    : vehicleId(vehicleId)
    , target(target)
{
}

void to_json(nlohmann::json& json, const ActionData& actionData)
{
    json = nlohmann::json{ { "vehicle_id", actionData.GetVehicleId() },
                           { "target", actionData.GetTarget() } };
}

void from_json(const nlohmann::json& json, ActionData& actionData)
{
    actionData.SetVehicleId(json.at("vehicle_id"));
    json.at("target").get_to(actionData.GetTarget());
}
