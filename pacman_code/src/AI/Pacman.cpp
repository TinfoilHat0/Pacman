/*
 * Pacman.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: mustafa
 */

#include "Pacman.h"
using namespace std;
/* This controller utilises 3 tactics, in order of importance:
 * 1. Get away from any non-edible ghost that is in close proximity
 * 2. Go after the nearest edible ghost
 * 3. Go to the nearest pill/power pill
 */
Node Pacman::simpleAI(Map map, const std::vector<Node> &nodeList,
		std::vector<Ghost> &ghostList, std::vector<Model> &pillList,
		std::vector<Model> &powerpillList, std::vector<Model> &targetList) {
	Node nextNode;
	Node nextTarget;
	bool nextNodeFound = false;

	//1. Get away from non-edible ghosts
	int maxDistance = 3;
	for (int i = 0; i < ghostList.size(); i++) {
		double distance = this->currentNode.getDistance(
				ghostList[i].getCurrentNode(), 'e');
		if (!ghostList[i].isEdible() && distance < maxDistance) {
			nextNode = map.getNextMoveAwayFromTarget(this->getCurrentNode(),
					ghostList[i].getCurrentNode(), nodeList);

			this->setState("Evading");
			nextNodeFound = true;
			break;
		}
	}

	//2. Go after nearest edible ghost
	if (!nextNodeFound) {
		for (int i = 0; i < ghostList.size(); i++) {
			if (ghostList[i].isEdible()) { //if there's atleast one edible ghost, search all over them to find the nearest.
				//std::cout << ghostList[i].getName() << std::endl;
				nextTarget = this->getNearestEdibleGhost(ghostList);
				nextNode = map.getNextMoveTowardsTarget(this->getCurrentNode(),
						nextTarget, nodeList);

				this->setState("Chasing");
				nextNodeFound = true;
				break;
			}

		}
	}

	//3. Go after nearest pill
	if (!nextNodeFound) {
		for (int i = 0; i < pillList.size(); i++) {
			if (pillList[i].isAlive()) { //if there's atleast a pill, search all over them to find the nearest.
				nextTarget = this->getNearestPill(pillList, powerpillList);
				nextNode = map.getNextMoveTowardsTarget(this->getCurrentNode(),
						nextTarget, nodeList);

				this->setState("Picking");
				nextNodeFound = true;
				break;
			}
		}
	}
	this->eatTarget(pillList, powerpillList, ghostList);
	return nextNode;

}

Node Pacman::getNearestEdibleGhost(const std::vector<Ghost> &ghostList) {
	double min = 999;
	double distance = 0;
	Node targetGhost;

	for (int i = 0; i < ghostList.size(); i++) {
		if (ghostList[i].isEdible()) {
			distance = this->getCurrentNode().getDistance(
					ghostList[i].getCurrentNode(), 'e');
			if (distance < min) {
				min = distance;
				targetGhost = ghostList[i].getCurrentNode();
			}

		}
	}

	return targetGhost;
}

Node Pacman::getNearestPill(const std::vector<Model> &pillList,
		const std::vector<Model> &powerpillList) {
	double min = 999;
	double distance = 0;
	Node nearestCoin;
	Model hold;
	for (int i = 0; i < pillList.size(); i++) {
		if (pillList[i].isAlive()) {
			distance = this->getCurrentNode().getDistance(
					pillList[i].getCurrentNode(), 'e');
			if (distance < min) {
				min = distance;
				nearestCoin = pillList[i].getCurrentNode();
				hold = pillList[i];
			}
		}
	}
	for (int i = 0; i < powerpillList.size(); i++) {
		if (powerpillList[i].isAlive()) {
			distance = this->getCurrentNode().getDistance(
					powerpillList[i].getCurrentNode(), 'e');
			if (distance < min) {
				min = distance;
				nearestCoin = powerpillList[i].getCurrentNode();
				hold = powerpillList[i];
			}
		}
	}
	return nearestCoin;
}

void Pacman::eatTarget(std::vector<Model> &pillList,
		vector<Model> &powerpillList, std::vector<Ghost> &ghostList) {
	for (int i = 0; i < pillList.size(); i++) {
		if (pillList[i].isAlive()
				&& this->getCurrentNode().equal(pillList[i].getCurrentNode())) {
			pillList[i].setAlive(false);
			this->score += 5;
		}
	}

	for (int i = 0; i < powerpillList.size(); i++) {
		if (powerpillList[i].isAlive()
				&& this->getCurrentNode().equal(
						powerpillList[i].getCurrentNode())) {

			for (int i = 0; i < ghostList.size(); i++) {
				ghostList[i].setEdible(true);
			}
			powerpillList[i].setAlive(false);
			this->score += 10;
		}
	}

	for (int i = 0; i < ghostList.size(); i++) {
		if (ghostList[i].isEdible()
				&& (this->currentNode.getX()
						== ghostList[i].getCurrentNode().getX()
						&& this->currentNode.getY()
								== ghostList[i].getCurrentNode().getY())) {
			ghostList[i].setAlive(false);
			this->score += 50;
		}
	}

}

Pacman::~Pacman() {
	// TODO Auto-generated destructor stub
}

