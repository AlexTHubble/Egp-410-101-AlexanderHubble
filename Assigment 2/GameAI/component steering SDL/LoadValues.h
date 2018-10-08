#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "FlockSteering.h"

class LoadValues :public GameMessage
{
public:
	LoadValues(Flock* steeringToLoadTo);
	~LoadValues();

	void process();
private:
	/*UnitManager * mpUnitManager;*/
	Flock * mpFlockSteering;
	string mFileName = "FlockValues.txt";
	//string mPath = "..\\..\\..\\Midterm,centipede\\Assets\\Files\\Data.txt";
	//C:\Users\ahubb\Documents\GitHub\Egp-410-\Assigment 2\GameAI\component steering SDL\Files

};