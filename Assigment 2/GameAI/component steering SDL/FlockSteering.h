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

	float mAllignWeight = 0.2;
	float mSeperationWeight = 0.4;
	float mCohesionWeigth = 0.3;
	//UnitManager* mUnitManager;

};