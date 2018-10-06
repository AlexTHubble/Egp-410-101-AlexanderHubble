#include "FlockSteering.h"
#include <map>
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


Flock::Flock(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mWanderSteering = new WanderSteering(mOwnerID, mTargetID);
}

Flock::~Flock()
{
	delete mWanderSteering;
}

Steering * Flock::getSteering()
{
	//std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap(); //Gets the unit map from mUnitManager, this will act as our neigberhood
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float tempX;
	float tempY;

	//Declare allign, seperation, and cohesion
	mAllignSteering = new Allign(mOwnerID, mTargetLoc, mTargetID);
	mSeperationSteering = new Seperation(mOwnerID, mTargetLoc, mTargetID);
	mCohesionSteering = new Cohesion(mOwnerID, mTargetLoc, mTargetID);

	//Get the vectors out of each algorithm
	Vector2D allignVector = mAllignSteering->getAlligment();
	Vector2D seperationVector = mSeperationSteering->getSeperation();
	Vector2D cohesionVector = mCohesionSteering->getCohesion();


	Steering* wanderSteering = mWanderSteering->getSteering();
	data = wanderSteering->getData();

	allignVector *= mAllignWeight;
	seperationVector *= mSeperationWeight;
	cohesionVector *= mCohesionWeigth;

	Vector2D newAcceleration = data.vel + allignVector + seperationVector + cohesionVector;
	newAcceleration.normalize();

	newAcceleration *= data.maxAccMagnitude;

	data.vel = newAcceleration;

	delete mCohesionSteering;
	delete mSeperationSteering;
	delete mAllignSteering;

	this->mData = data;
	return this;
}
