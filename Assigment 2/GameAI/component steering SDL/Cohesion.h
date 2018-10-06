#include <Trackable.h>
#include "Steering.h"
#include <map>
#include "Unit.h"


class Cohesion : public Steering
{
public:
	Cohesion(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	Vector2D getCohesion();
protected:

	float mNeighborRadius = 200;
};