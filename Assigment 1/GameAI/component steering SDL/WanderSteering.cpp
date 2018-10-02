#include "WanderSteering.h"
#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


const float PI = 3.1456;
const float RADIAN_TO_DEGREE = 180 / PI;
const float DEGREE_TO_RADIAN = PI / 180;


WanderSteering::WanderSteering(const UnitID & ownerID, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
}

Steering * WanderSteering::getSteering()
{
	//setTargetLoc(getWanderTarget());
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	mWanderOrientation = pOwner->getFacing();

	mWanderOrientation += genRandomBinomial() * mWanderRate; //Update wander orientation
	Vector2D ownerOrientation = (cos(pOwner->getFacing()), sin(pOwner->getFacing()));
	mTargetOrientation = mWanderOrientation + pOwner->getFacing(); //Calculate combined orientation

	mTarget = pOwner->getPositionComponent()->getPosition() + ownerOrientation * mWanderOffSet; //Calculate center of wander circle
	//target += wanderOrientation * targetOrientation;

	mTarget += Vector2D(cos(mTargetOrientation), sin(mTargetOrientation)) * mWanderRadius;

	//Get steering data from face steering
	mpFaceSteering = new FaceSteering(mOwnerID, mTarget, mTargetID);
	Steering * newSteering = mpFaceSteering->getSteering(); //NOTE: Figure out how to get working wihtout making getSteering public
	data = newSteering->getData();


	Vector2D direction = mTarget - pOwner->getPositionComponent()->getPosition();
	Vector2D targetVelocity = direction * data.maxSpeed;

	data.acc = targetVelocity - data.vel;

	std::cout << "Current wander target: " << mTarget.getX() << " " << mTarget.getY() << std::endl;

	this->mData = data;
	delete newSteering;
	return this;
}

Vector2D WanderSteering::getWanderTarget()
{
	return Vector2D();
}
