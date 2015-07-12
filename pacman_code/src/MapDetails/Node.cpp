/*
 * Node.cpp
 *
 *  Created on: Mar 2, 2014
 *      Author: mustafa
 */
#include "Node.h"
using namespace std;
Node::Node() {
	// TODO Auto-generated destructor stub
}
Node::~Node() {
	// TODO Auto-generated destructor stub
}
Node::Node(int x, int y, bool occupied) {
	this->x = x;
	this->y = y;
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->occupied = occupied;

	this->parent = NULL;
}
Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
	this->parent = NULL;
}
bool Node::equal(Node node) {
	if (this->x == node.x && this->y == node.y)
		return true;
	else
		return false;
}
Node Node::getNode(vector<Node> nodeList) {
	for (int i = 0; i < nodeList.size(); i++) {
		if (this->x == nodeList[i].x && this->y == nodeList[i].y) {
			return nodeList[i];
			break;
		}
	}
}
int Node::getDistance(Node target, char type) {
	//returns manhattan distance
	if (type == 'm')
		return abs(this->x - target.x) + abs(this->y - target.y);
	//returns euclidian distance
	if ( type == 'e')
		return sqrt((this->x - target.x)*(this->x - target.x) + (this->y - target.y)*(this->y - target.y));

}

void Node::getWalkableAdjacentNodes(vector<Node> nodeList,
		vector<Node>&adjacentNodes) {
	for (int i = 0; i < nodeList.size(); i++) {
		if (!nodeList[i].occupied) {
			//check NORTH of the current node
			if (nodeList[i].y == this->y + 1 && nodeList[i].x == this->x) {
				adjacentNodes.push_back(nodeList[i]);
			}
			//check SOUTH of the current node
			if (nodeList[i].y == this->y - 1 && nodeList[i].x == this->x) {
				adjacentNodes.push_back(nodeList[i]);
			}
			//check EAST of the current node
			if (nodeList[i].x + 1 == this->x && nodeList[i].y == this->y) {
				adjacentNodes.push_back(nodeList[i]);
			}
			//check WEST of the current node
			if (nodeList[i].x - 1 == this->x && nodeList[i].y == this->y) {
				adjacentNodes.push_back(nodeList[i]);
			}
		}
	}
}
