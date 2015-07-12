/*
 * Map.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: mustafa
 */

#include "Map.h"
using namespace std;
Map::Map() {
	// TODO Auto-generated constructor stub

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

Node Map::getNextMoveTowardsTarget(const Node &start, const Node &end,
		const std::vector<Node> &nodeList) {
	vector<Node> path = findPath(start, end, nodeList);
	return path[1]; //0th index holds the current node, 1st index holds the next node.

}

Node Map::getNextMoveAwayFromTarget(Node start, Node end,
		const std::vector<Node> &nodeList) {
	Node nextNode;
	vector<Node> adjacentNodes;
	start.getWalkableAdjacentNodes(nodeList, adjacentNodes);
	//1st option

	int max = 0;
	double distance = 0;
	for (int i = 0; i < adjacentNodes.size(); i++) {
		distance = adjacentNodes[i].getDistance(end, 'e');
		if (distance > max) {
			max = distance;
			nextNode = adjacentNodes[i];
		}
	}

	return nextNode;

}

Node Map::getRandomMove(Node start, const std::vector<Node> &nodeList) {
	vector<Node> adjacentNodes;
	start.getWalkableAdjacentNodes(nodeList, adjacentNodes);
	srand(time(0));
	return adjacentNodes[rand() % adjacentNodes.size()];

}

Node nodeWithLowestFScore(vector<Node> openList) {
	int fMin = 99999;
	Node minNode = openList[0];
	for (int i = 0; i < openList.size(); i++) {
		if (openList[i].getF() <= fMin) {
			fMin = openList[i].getF();
			minNode = openList[i];
		}
	}
	return minNode;
}
void removeFromVector(vector<Node> &nodeList, Node toRemove) {
	for (int i = 0; i < nodeList.size(); i++) {
		if (toRemove.equal(nodeList[i])) {
			nodeList.erase(nodeList.begin() + i);
			break;
		}
	}
}
bool inVector(vector<Node> nodeList, Node node) {
	for (int i = 0; i < nodeList.size(); i++) {
		if (nodeList[i].equal(node))
			return true;
	}
	return false;
}

vector<Node> Map::findPath(const Node &start, const Node &end,
		vector<Node> nodeList) {
	Node targetNode = end;
	Node startNode = start;

	vector<Node> openList;
	vector<Node> closedList;
	vector<Node> path;

	openList.push_back(startNode);
	while (!openList.empty()) {
		Node curNode = nodeWithLowestFScore(openList);
		Node *toParent = new Node;
		*toParent = curNode;
		closedList.push_back(curNode);
		if (curNode.equal(targetNode)) {
			Node *p = &curNode;
			while (p) {
				path.push_back(*p);
				p = p->getParent();
			}
			delete toParent;
			break;
		}

		removeFromVector(openList, curNode);
		vector<Node> adjNodes;
		curNode.getWalkableAdjacentNodes(nodeList, adjNodes);
		for (int i = 0; i < adjNodes.size(); i++) {
			if (inVector(closedList, adjNodes[i])) {
				continue;
			}
			if (!inVector(closedList, adjNodes[i])) {

				adjNodes[i].setParent(toParent);
				adjNodes[i].setG(curNode.getG() + 1);
				adjNodes[i].setH(adjNodes[i].getDistance(targetNode, 'm'));
				adjNodes[i].setF();
				openList.push_back(adjNodes[i]);
			}
			if (inVector(closedList, adjNodes[i])) {
				if (curNode.getG() + 1 < adjNodes[i].getG()) {
					adjNodes[i].setParent(&curNode);
					adjNodes[i].setG(curNode.getG() + 1);
					adjNodes[i].setF();
				}
			}
		}
	}
	reverse(path.begin(), path.end());
	return path;
}

