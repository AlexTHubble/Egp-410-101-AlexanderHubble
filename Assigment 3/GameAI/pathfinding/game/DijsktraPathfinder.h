#pragma once

#include "GridPathfinder.h"
#include <vector>

using namespace std;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class Dijsktra :public GridPathfinder
{
public:
	Dijsktra(Graph* pGraph);
	~Dijsktra();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
	struct NodeRecord : public Trackable
	{
	public:


		NodeRecord() : mNode(NULL), mConnection(NULL), mCost(0) {}
		NodeRecord(Node* node, Connection* connection, int cost) : mNode(node), mConnection(connection), mCost(cost) {}


		Node * mNode;
		Connection* mConnection;
		int mCost;


	};
};

