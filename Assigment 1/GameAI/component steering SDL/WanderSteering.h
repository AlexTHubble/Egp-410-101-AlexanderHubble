#include <Trackable.h>
#include "Steering.h"
//#include "FaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const UnitID& targetID = INVALID_UNIT_ID);
	//friend FaceSteering;
	//friend Steering;
	virtual Steering* getSteering();
protected:

	Vector2D getWanderTarget();
	//float mTargetRotationRadius = 5;
	//float slowRadius = 5;
	//float maxRotation = 10;
	float mWanderOffSet = 100;
	float mWanderRadius = 50;
	float mWanderRate = 2 * 3.14;
	float mWanderOrientation = 0;
	float mTargetOrientation = 0;
	Vector2D mTarget;

	Steering* mpFaceSteering;
};