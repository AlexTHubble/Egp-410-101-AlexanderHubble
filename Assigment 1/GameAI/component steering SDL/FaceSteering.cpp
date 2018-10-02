#include "FaceSteering.h"
//#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


const float PI = 3.1456;
const float RADIAN_TO_DEGREE = 180 / PI; //Formula for converting a radian to a degree
const float DEGREE_TO_RADIAN = PI / 180; //Fomula for converting a degree to a radian 


FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLocation, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLocation);
}

Steering * FaceSteering::getSteering()
{

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float rotationToTarget = atan2(direction.getY(), direction.getX()) + .5f * PI;
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Vector2D rotation = mTargetFacing - pOwner->getFacing();

	//Converts to a 2Pi interval
	float currentRotation = fmod(pOwner->getFacing(), 2.0 * PI);
	float rotationSize = rotationToTarget - currentRotation;
	float rotationSpeed = 0;

	std::cout << currentRotation * RADIAN_TO_DEGREE << "\t" << rotationToTarget*RADIAN_TO_DEGREE << std::endl;

	if (abs(rotationSize) < mTargetRotationRadius * DEGREE_TO_RADIAN) //If facing target, stop rotation
	{
		data.rotAcc = 0;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}
		

	//if (rotationSize > mSlowRadius * DEGREE_TO_RADIAN) //If it outside the slow radius, keep rotating at max speed...
	//{
	//	rotationSpeed = data.maxRotVel;
	//}
	//else //Else move at a slower speed
	//{
	//	rotationSpeed = data.maxRotVel * rotationSize / (mSlowRadius * DEGREE_TO_RADIAN);
	//}

	//targetRotation *= currentRotation / rotationSize;

	data.rotAcc = rotationToTarget - pOwner->getFacing();
	data.rotAcc /= 0.1;

	if (data.rotAcc > data.maxRotAcc) //If rotatating too fast, slow down
	{
		data.rotAcc /= abs(data.rotAcc);
		data.rotAcc *= data.maxRotAcc;
	}

	if (rotationSize > 0) //If the rotation is needed to go in a positive direction, move in a positive direction
	{
		data.rotAcc = abs(data.rotAcc);
	}
	else if (rotationSize < 0) //If the rotation is needed to go in a negavitve direction, move in a negative direction
	{
		data.rotAcc = -abs(data.rotAcc);
	}

	this->mData = data;
	return this;
}
