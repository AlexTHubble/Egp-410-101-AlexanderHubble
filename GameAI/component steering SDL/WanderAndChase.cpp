#include <cassert>

#include "WanderAndChase.h"
//#include "SeekSteering.h"
#include "Arrive.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "FaceSteering.h"
#include "Unit.h"

WanderAndChase::WanderAndChase(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
{
	setOwnerID(ownerID);
	setTargetLoc(targetLoc);
	setTargetID(targetID);
}

Steering * WanderAndChase::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID) //If seeking a unit, set target location to the unit's location
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
		//delete pTarget;
	}

	Vector2D direction = mTargetLoc- pOwner->getPositionComponent()->getPosition(); //Gets the distance between the character and the target
	float distance = direction.getLength();

	WanderSteering * wanderSteering = new WanderSteering(mOwnerID, mTargetID);
	Arrive * arriveSteering = new Arrive(mOwnerID, mTargetLoc, mTargetID);
	FaceSteering * faceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);

	if (distance > mDetectionRadius) //If outside radius wander...
	{
		Steering * wanderSteeringData = wanderSteering->getSteering();

		data = wanderSteeringData->getData();

	}
	else //Else seek and face
	{
		Steering * faceSteeringData = faceSteering->getSteering();
		Steering * arriveSteeringData = arriveSteering->getSteering();

		PhysicsData facePhysicsData = faceSteeringData->getData();
		PhysicsData arrivePhysicsData = arriveSteeringData->getData();
		data.acc = arrivePhysicsData.acc;
		data.rotAcc = facePhysicsData.rotAcc;
		data.rotVel = facePhysicsData.rotVel;
	}


	delete wanderSteering;
	delete arriveSteering;
	delete faceSteering;

	this->mData = data;
	return this;
}
