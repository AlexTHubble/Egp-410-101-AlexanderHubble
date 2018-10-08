#include "LoadValues.h"
#include "UnitManager.h"
#include "SteeringComponent.h"
#include <fstream>
#include <string>

LoadValues::LoadValues(Flock * steeringToLoadTo)
	:GameMessage(LOAD_DATA)
{

	mpFlockSteering = steeringToLoadTo;
}

LoadValues::~LoadValues()
{
	delete mpFlockSteering;
}

void LoadValues::process()
{
 	ifstream fout;

	//string line;
	string variableName;
	string data;

	fout.open(mFileName);


	if (fout.is_open())
	{
		while (!fout.eof())
		{
			getline(fout, variableName, '=');
			if (variableName == "\nAllignWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setAllignWeight(output);
			}
			else if (variableName == "\nSeperationWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setSeperationWeight(output);
			}
			else if (variableName == "\nCohesionWeigth")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setCohesionWeight(output);
			}
			else if (variableName == "\nWanderWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderWeight(output);
			}
			else if (variableName == "\nWanderOffSet")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderOffSet(output);
			}
			else if (variableName == "\nWanderRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderRadius(output);
			}
			else if (variableName == "\nWanderRate")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderRate(output);
			}
			else if (variableName == "\nAllignRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setAllignmentRadius(output);
			}
			else if (variableName == "\nSeperationRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setSeperationRadius(output);
			}
			else if (variableName == "\nCohesionRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setCohesionRadius(output);
			}
			else
			{
				getline(fout, data, ';');
			}
		}
	}
	fout.close();

}
