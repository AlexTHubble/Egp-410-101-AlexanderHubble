#include "DijsktraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

Dijsktra::Dijsktra(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

Dijsktra::~Dijsktra()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* Dijsktra::findPath(Node* pFrom, Node* pTo)
{
	cout << "Beginging path finding Dijsktra..." << endl;

	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	//Sets up first node
	NodeRecord fromNodeRecord = NodeRecord(pFrom, NULL, 0);


	//Sets up the open list
	list<NodeRecord> openNodes;
	openNodes.push_front(fromNodeRecord);
	list<NodeRecord> closedNodes;

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	//create Path
	//Path* pVisted = new Path();
	Path* shortestPath = new Path();

	NodeRecord currentNodeRecord;
	bool toNodeAdded = false;

	/*cout << "Begining open node list search" << endl;*/
	//Prosses through each open node
	while (openNodes.size() > 0)
	{
		
		//get current node from front of list
		currentNodeRecord = openNodes.front();

		//remove node from list
		openNodes.pop_front();

		//If the current node is not the target
		if (currentNodeRecord.mNode == pTo)
		{
			break;
		}
		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(currentNodeRecord.mNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			/*cout << "Beginin connection search" << endl;*/

			bool isInClosed = false; //If the node has been found in the closed list
			bool isInOpen = false; //If the node has been found in the open list
			bool isTarget = false;

			//Sets up connection & node
			Connection* nodeConnection = connections[i];
			NodeRecord endRecord;

			Node* endNode = connections[i]->getToNode();
			float endNodeCost = currentNodeRecord.mCost + connections[i]->getCost();

			//Looks for the current node in the closed list
			for (list<NodeRecord>::iterator nodeRecordIterator = closedNodes.begin(); nodeRecordIterator != closedNodes.end(); nodeRecordIterator++)
			{
				/*cout << "Beginin imbeded for loop 1" << endl;*/
				if (nodeRecordIterator->mNode == endNode) //If it was found...
				{
					isInClosed = true;
					break;
				}
			}
			/*cout << "End imbeded for loop 1" << endl;*/

			//Looks for the node in the open list
			for (list<NodeRecord>::iterator nodeRecordIterator = openNodes.begin(); nodeRecordIterator != openNodes.end(); nodeRecordIterator++)
			{
				/*cout << "Beginin imbeded for loop 2" << endl;*/
				if (nodeRecordIterator->mNode == endNode) //If it was found...
				{
					endNode = nodeRecordIterator->mNode; //Set the end node to the one found

					isInOpen = true;
					break;
				}
			}
			/*cout << "End imbeded for loop 2" << endl;*/


			//If the node was found in the closed list continue
			if (isInClosed)
			{
				continue;
			}
			//If the node was found in the open list and the cost of the one found is more effeciant
			else if (isInOpen && endRecord.mCost <= endNodeCost)
			{
				continue;
			}
			//If it wasn't found in either list, set up the end record for use
			else
			{
				endRecord = NodeRecord(endNode, nodeConnection, endNodeCost);
				//endRecord.mNode = endNode;
				//endRecord.mConnection = nodeConnection;
				//endRecord.mCost = endNodeCost;
			}

			//Add endNode to open list
			if (!isInOpen && !isTarget)
			{
				openNodes.push_back(endRecord);
				if (endRecord.mNode == pTo)
				{
					isTarget = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(endRecord.mNode);
#endif // VISUALIZE_PATH

				closedNodes.push_back(endRecord);
			}

			/*cout << "End connection search" << endl;*/
		} //END OF CONNECTION FOR LOOP

		for (list<NodeRecord>::iterator openNodeRecordIterator = openNodes.begin(); openNodeRecordIterator != openNodes.end(); openNodeRecordIterator++)
		{
			/*cout << "Beginin imbeded for loop 3" << endl;*/
			if (openNodeRecordIterator->mNode == currentNodeRecord.mNode)
			{
				openNodes.erase(openNodeRecordIterator);
				break;
			}
		}
		/*cout << "End imbeded for loop 3" << endl;*/

#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentNodeRecord.mNode);
#endif // VISUALIZE_PATH

		
	} //END OF OPEN NODES FOR LOOP
	/*cout << "End open node list search" << endl;*/


	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	//If the node has not been found break out of the algorithm
	if (currentNodeRecord.mNode != pTo)
	{
		cout << "Not found" << endl;

		return NULL;
	}

	//Gets the path from the target to the the begining
	while (currentNodeRecord.mNode != pFrom)
	{
		cout << "Beginin creating path" << endl;

		shortestPath->addNode(currentNodeRecord.mNode);
		currentNodeRecord.mNode = currentNodeRecord.mConnection->getFromNode();

		//Finds the current node in the closed node list, then returns it's connection
		for (list<NodeRecord>::iterator closedNodeRecordIterator = closedNodes.begin(); closedNodeRecordIterator != closedNodes.end(); closedNodeRecordIterator++)
		{
			if (closedNodeRecordIterator->mNode == currentNodeRecord.mNode)
			{
				currentNodeRecord.mConnection = closedNodeRecordIterator->mConnection;
				break;
			}
		}

		cout << "End creating path" << endl;
	}

#ifdef VISUALIZE_PATH
	mpPath = shortestPath;
#endif

	cout << "Ended path finding Dijsktra..." << endl;

	return shortestPath;

}

