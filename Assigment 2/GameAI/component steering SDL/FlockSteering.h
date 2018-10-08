#include <Trackable.h>
#include "Steering.h"
#include "UnitManager.h"
#include "AllignSteering.h"
#include "Seperation.h"
#include "Cohesion.h"
#include "WanderSteering.h"

class Flock : public Steering
{
public:
	Flock(const UnitID& ownerID, const Vector2D& targetLoc,const UnitID& targetID = INVALID_UNIT_ID);
	~Flock();
	//void setUnitManager(UnitManager *unitManager) { mUnitManager = unitManager; };
	
protected:
	virtual Steering* getSteering();

	Allign *mAllignSteering;
	Seperation *mSeperationSteering;
	Cohesion *mCohesionSteering;
	WanderSteering *mWanderSteering;

	float mAllignWeight = 0.4;
	float mSeperationWeight = 1.0;
	float mCohesionWeigth = 0.6;
	float mWanderWeight = 0.3;

	float mWanderOffSet = 100.0f;
	float mWanderRadius = 50.0f;
	float mWanderRate = 0.8f;
	float mWanderOrientation = 0;
	float mTargetOrientation = 0;
	Vector2D mTarget;

	Steering* mpFaceSteering;

};