#ifndef SERVER_MEDIUMTANK_H
#define SERVER_MEDIUMTANK_H

#include "abstracttank.h"

class MediumTank : public AbstractTank
{
public:
    MediumTank(int vehicleId);
    virtual ~MediumTank();

    // TODO: Implement methods
    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
void to_json(nlohmann::json& j, const MediumTank& tank);

void from_json(const nlohmann::json& j, MediumTank& tank);

#endif // SERVER_MEDIUMTANK_H
