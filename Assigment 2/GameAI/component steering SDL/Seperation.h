#include <Trackable.h>
#include "Steering.h"



class Seperation : public Steering
{
public:
	Seperation(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	Vector2D getSeperation();
protected:

	float mNeighborRadius = 50;
};