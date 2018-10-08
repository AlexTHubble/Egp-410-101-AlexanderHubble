#include <Trackable.h>
#include "Steering.h"



class Allign : public Steering
{
public:
	Allign(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	Vector2D getAlligment();
protected:

	int mNeighborRadius = 300;
};