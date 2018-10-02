#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
	/*friend WanderSteering;*/
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLocation, const UnitID& targetID = INVALID_UNIT_ID);
	virtual Steering* getSteering();
protected:

	float mTargetRotationRadius = 5;
	float mSlowRadius = 5;
	float mMaxRotation = 10;
};